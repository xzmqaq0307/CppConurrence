#ifndef CHAPTER_1_H
#define CHAPTER_1_H

#if defined(CHAPTER_1_LIB)
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllexport)
#else
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllimport)
#endif

CHAPTER_EXPORT_ENTER void CcChapter1HelloWorld(const char* msgIn, char* msgOut);

#endif