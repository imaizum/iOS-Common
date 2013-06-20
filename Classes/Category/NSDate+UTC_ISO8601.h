@interface NSDate (UTC_ISO8601)

#pragma mark - UTC

//現在のUTCを返します
+ (NSDate*)UTC;

//指定した日付をUTCに変換します
+ (NSDate*)UTCWithDate:(NSDate*)date;

//NSDateのインスタンスをUTCに変換します
- (NSDate*)convertToUTC;

#pragma mark - ISO8601

//ISO8601形式の文字列を出力します
- (NSString*)ISO8601String;

//ISO8601形式の文字列から日付を作ります
+ (NSDate*)dateFromISO8601String:(NSString*)string;

@end
