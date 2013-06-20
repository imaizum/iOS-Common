@implementation NSURL (LibraryHandling)

+ (NSURL*)appLibraryDirectoryURL
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
    NSString* path = [paths objectAtIndex:0];
    NSURL* url = [NSURL fileURLWithPath:path isDirectory:YES];

    return url;
}

+ (NSURL*)appLibraryCacheDirectoryURL
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES);
    NSString* path = [paths objectAtIndex:0];
    NSURL* url = [NSURL fileURLWithPath:path isDirectory:YES];

    return url;
}

+ (NSURL*)userDocumentsDirectoryURL
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* path = [paths objectAtIndex:0];
    NSURL* url = [NSURL fileURLWithPath:path isDirectory:YES];

    return url;
}

@end
