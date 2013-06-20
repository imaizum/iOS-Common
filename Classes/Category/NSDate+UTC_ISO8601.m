@implementation NSDate (UTC_ISO8601)

#pragma mark - UTC

+ (NSDate*)UTC
{
    return [[NSDate UTCWithDate:[NSDate date]];
}

+ (NSDate*)UTCWithDate:(NSDate*)date
{
    NSTimeZone* localTimeZone = [NSTimeZone localTimeZone];
    NSTimeZone* utcTimeZone = [NSTimeZone timeZoneWithAbbreviation:@"UTC"];

    NSInteger currentGMTOffset = [localTimeZone secondsFromGMTForDate:date];
    NSInteger gmtOffset = [utcTimeZone secondsFromGMTForDate:date];
    NSTimeInterval gmtInterval = (NSTimeInterval)(gmtOffset - currentGMTOffset);

    return [[[NSDate alloc] initWithTimeInterval:gmtInterval sinceDate:date] autorelease];   
}

- (NSDate*)convertToUTC
{
    return [NSDate UTCWithDate:self];
}

#pragma mark - ISO8601

- (NSString*)ISO8601String
{
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyy-MM-dd'T'HH:mm:ssZ";
    NSString* dateString = [formatter stringFromDate:self];
    [formatter release];

    return dateString;
}

+ (NSDate*)dateFromISO8601String:(NSString*)string
{
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    formatter.dateFormat = @"yyyy-MM-dd'T'HH:mm:ssZ";
    NSDate* date = [formatter dateFromString:string];
    [formatter release];

    return date;
}

@end
