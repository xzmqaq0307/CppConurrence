#ifndef PRACTICE_4_H
#define PRACTICE_4_H

#if defined(PRACTICE_LIB)
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllexport)
#else
#define CHAPTER_EXPORT_ENTER extern "C" __declspec(dllimport)
#endif

CHAPTER_EXPORT_ENTER void CcPracticeRecordAndPlay(const char* msgIn, char* msgOut);

#endif