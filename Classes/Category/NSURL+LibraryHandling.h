@interface NSURL (LibraryHandling)

//<アプリケーション>/Library/へのショートカット
+ (NSURL*)appLibraryDirectoryURL;

//<アプリケーション>/Library/Caches/へのショートカット
+ (NSURL*)appLibraryCacheDirectoryURL;

//<アプリケーション>/Documents/へのショートカット
+ (NSURL*)userDocumentsDirectoryURL;

@end
