#include "utils.h"

#include <cassert>

namespace watermark
{

    Point position_by_layout(Layout layout, const Size &source_size, const Size &mark_size)
    {
        assert(!source_size.is_empty() && "source_size cannot be empty");
        assert(!mark_size.is_empty() && "mark_size cannot be empty");

        auto middle_height = static_cast<int>(source_size.height() / 2);
        auto middle_width = static_cast<int>(source_size.width() / 2);
        auto half_mark_height = static_cast<int>(mark_size.height() / 2);
        auto half_mark_width = static_cast<int>(mark_size.width() / 2);

        Point mark_pos{0, 0};
        switch (layout)
        {
        case Layout::Top_left:
        {
            mark_pos = Point{0, 0};
            break;
        }
        case Layout::Top_middle:
        {
            mark_pos = Point{middle_width - half_mark_width, 0};
            break;
        }
        case Layout::Top_right:
        {
            mark_pos = Point{source_size.width() - mark_size.width(), 0};
            break;
        }
        case Layout::Middle_left:
        {
            mark_pos = Point{0, middle_height - half_mark_height};
            break;
        }
        case Layout::Center:
        {
            mark_pos = Point{middle_width - half_mark_width, middle_height - half_mark_height};
            break;
        }
        case Layout::Middle_right:
        {
            mark_pos = Point{source_size.width() - mark_size.width(), middle_height - half_mark_height};
            break;
        }
        case Layout::Bottom_left:
        {
            mark_pos = Point{0, source_size.height() - mark_size.height()};
            break;
        }
        case Layout::Bottom_middle:
        {
            mark_pos = Point{middle_width - half_mark_width, source_size.height() - mark_size.height()};
            break;
        }
        case Layout::Bottom_right:
        {
            mark_pos = {source_size.width() - mark_size.width(), source_size.height() - mark_size.height()};
            break;
        }
        default:
            break;
        }

        return mark_pos;
    }

}
