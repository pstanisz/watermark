# Design concepts

## Basic API

Namespace

```cpp
namespace watermark
{
}
```

The easiest freestanding function

```cpp
void add_watermark(input_path, watermark_path, output_path, position, size);
```

C++ API to avoid unsafe conversions, read of null-terminated strings, etc.
