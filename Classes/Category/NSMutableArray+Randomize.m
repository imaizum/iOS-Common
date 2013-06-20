@implementation NSMutableArray (Randomize)

- (void)randomize
{
    NSUInteger count = [self count];

    for (NSUInteger i = 0; i < count; ++i) {
        NSUInteger j = (NSUInteger)(arc4random() % (i+1));
        [self exchangeObjectAtIndex:i withObjectAtIndex:j];
    }
}

@end
