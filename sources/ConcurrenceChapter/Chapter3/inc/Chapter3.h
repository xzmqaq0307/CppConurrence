#ifndef CHAPTER_3_H
#define CHAPTER_3_H

#if defined(CHAPTER_3_LIB)
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllexport)
#else
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllimport)
#endif

CHAPTER_EXPORT_ENTER void CcChapter2BackgroundTask(const char* msgIn, char* msgOut);

CHAPTER_EXPORT_ENTER void CcChapter2FuncOops(const char* msgIn, char* msgOut);

CHAPTER_EXPORT_ENTER void CcChapter2FuncOopsWithException(const char* msgIn, char* msgOut);

CHAPTER_EXPORT_ENTER void CcChapter2FuncOopsWithRAII(const char* msgIn, char* msgOut);

#endif