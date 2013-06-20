@interface UIColor (HexColoring)

//RGBAを16進数型(ffa500ffなど)で指定します
+ (UIColor*)colorWithHex:(uint32_t)hex;

@end
