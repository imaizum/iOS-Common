@implementation UIColor (HexColoring)

+ (UIColor*)colorWithHex:(uint32_t)hex
{
    CGFloat red = ((hex & 0xFF000000) >> 24) / 255.0f;
    CGFloat green = ((hex & 0x00FF0000) >> 16) / 255.0f;
    CGFloat blue = ((hex & 0x0000FF00) >> 8) / 255.0f;
    CGFloat alpha = (hex & 0x0000000FF) / 255.0f;

    return [UIColor colorWithRed:red green:green blue:blue alpha:alpha];
}
