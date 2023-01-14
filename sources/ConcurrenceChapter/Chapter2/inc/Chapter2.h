#ifndef CHAPTER_2_H
#define CHAPTER_2_H

#if defined(CHAPTER_2_LIB)
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllexport)
#else
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllimport)
#endif

CHAPTER_EXPORT_ENTER void CcChapter2BackgroundTask(const char* msgIn, char* msgOut);

CHAPTER_EXPORT_ENTER void CcChapter2FuncOops(const char* msgIn, char* msgOut);

#endif