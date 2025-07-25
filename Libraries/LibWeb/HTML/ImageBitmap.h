/*
 * Copyright (c) 2024, Lucas Chollet <lucas.chollet@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/OwnPtr.h>
#include <LibGfx/Bitmap.h>
#include <LibWeb/Bindings/PlatformObject.h>
#include <LibWeb/Bindings/Serializable.h>
#include <LibWeb/Bindings/Transferable.h>
#include <LibWeb/Forward.h>
#include <LibWeb/HTML/Canvas/CanvasDrawImage.h>

namespace Web::HTML {

using ImageBitmapSource = FlattenVariant<CanvasImageSource, Variant<GC::Root<FileAPI::Blob>, GC::Root<ImageData>>>;

// https://html.spec.whatwg.org/multipage/imagebitmap-and-animations.html#imagebitmapoptions
struct ImageBitmapOptions {
    // FIXME: Implement these fields
};

class ImageBitmap final : public Bindings::PlatformObject
    , public Web::Bindings::Serializable
    , public Web::Bindings::Transferable {
    WEB_PLATFORM_OBJECT(ImageBitmap, Bindings::PlatformObject);
    GC_DECLARE_ALLOCATOR(ImageBitmap);

public:
    static GC::Ref<ImageBitmap> create(JS::Realm&);
    virtual ~ImageBitmap() override = default;

    // ^Web::Bindings::Serializable
    virtual HTML::SerializeType serialize_type() const override { return HTML::SerializeType::ImageBitmap; }
    virtual WebIDL::ExceptionOr<void> serialization_steps(HTML::TransferDataEncoder&, bool for_storage, HTML::SerializationMemory&) override;
    virtual WebIDL::ExceptionOr<void> deserialization_steps(HTML::TransferDataDecoder&, HTML::DeserializationMemory&) override;

    // ^Web::Bindings::Transferable
    virtual WebIDL::ExceptionOr<void> transfer_steps(HTML::TransferDataEncoder&) override;
    virtual WebIDL::ExceptionOr<void> transfer_receiving_steps(HTML::TransferDataDecoder&) override;
    virtual HTML::TransferType primary_interface() const override;

    WebIDL::UnsignedLong width() const;
    WebIDL::UnsignedLong height() const;

    void close();

    // Implementation specific:
    void set_bitmap(RefPtr<Gfx::Bitmap>);
    Gfx::Bitmap* bitmap() const;

private:
    explicit ImageBitmap(JS::Realm&);

    // FIXME: We don't implement this flag yet:
    // An ImageBitmap object's bitmap has an origin-clean flag, which indicates whether the bitmap is tainted by content
    // from a different origin. The flag is initially set to true and may be changed to false by the steps of
    // createImageBitmap().

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    WebIDL::UnsignedLong m_width = 0;
    WebIDL::UnsignedLong m_height = 0;

    RefPtr<Gfx::Bitmap> m_bitmap { nullptr };
};

}
