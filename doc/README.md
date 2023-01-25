# Design concepts

## Basic API

Namespace

```cpp
namespace watermark
{
}
```

The easiest freestanding function?

```cpp
void add_watermark(input_path, watermark_path, output_path, position, size);
```

C++ API to avoid unsafe conversions, read of null-terminated strings, etc.

Image class for loading the image in easy, intuitive, OO-way?

```cpp
auto logo = Image{"/path/to/image.png"};
```

Maybe such an API?

```cpp
    Image img{"../tools/proto/data/test_img_1.png"};
    Image logo{"../tools/proto/data/test_logo_1.png"};

    Watermark mark{std::move(logo)};
    auto result = img.apply(mark);

    result.save("test_img_1_mark.png");
```

Maybe better?

```cpp
    Image img{"../tools/proto/data/test_img_1.png"};
    Image logo{"../tools/proto/data/test_logo_1.png"};

    Watermark mark{std::move(logo)};
    auto result = mark.apply_to(img);
```

Adv: single mark can be used for many images

Where, how to set mark parameters? Size, position, other?

Maybe:

```cpp
    Watermark mark{std::move(logo)};

    // Layout alternatives:
    mark.set_layout(Waterkark::Layout::Botto_right);
    mark.set_layout(Waterkark::Position{10, 10});

    // Size alternatives:
    mark.set_size(Watermark::Size::Fit_to_image);
    mark.set_size(Watermark::Size::Scale{0.1});
    mark.set_size(Waterkark::Size{100, 100});
```

First version: watermark size and position, this will be a base for all other options

Non-copyable, move-only, pImpl pattern, lightweight (no plan to use inheritance).

## Testing

### Unit testing

After a while... UT of opencv wrappers make no bigger sense...

### Functional testing

### Other?
