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

Non-copyable, move-only, pImpl pattern, lightweight (no plan to use inheritance).
