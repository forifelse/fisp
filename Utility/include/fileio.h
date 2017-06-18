/*-----------------------------------------------------------
Name:		fisp
Author:		fisper@163.com
Date:		2016.12
Copyright (c). All rights reserved.
------------------------------------------------------------*/

#pragma once
#include <string>
#include <fstream>
#include "base.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class EFileMode
		------------------------------------------------------------*/
		enum EFileMode
		{
			File_Mode_Read,
			File_Mode_Write,
			File_Mode_WriteAppend,
			File_Mode_WriteATE,
			File_Mode_ReWrite,	// clear all and re-write
			File_Mode_Binary,
			File_Mode_ReadWrite,
			File_Mode_ReReadWrite,
			File_Mode_Max
		};

		/*-----------------------------------------------------------
		class IFileIO
		------------------------------------------------------------*/
		class IFileIO : public IRoot
		{
		public:
			virtual bool open(const String& strPathFile, const EFileMode& eMode) = 0;
			virtual void close() = 0;
			virtual bool read(String &strRead) const = 0;
			virtual bool read(String &strRead, ulong uSize, ulong uFrom = 0) const = 0;
			virtual bool write(const String& strWrite) = 0;
			virtual void writeEnter() = 0;
			virtual bool readPage(String &strPage, ulong* curSeek = NULL) = 0;
			virtual bool writePage(const String& strPage, ulong* curSeek = NULL) = 0;
			virtual void resetPageSeek(ulong uSeek = 0) = 0;
			virtual bool insert(const String& strInsert, ulong uIndex) = 0;
			virtual bool remove(ulong uIndex, ulong uCount, String* strRemoved = NULL) = 0;
			virtual bool clearText() = 0;
			virtual void flush() = 0;
			virtual bool isOpen() const = 0;
			virtual ulong getSize() const = 0;
			virtual void setReadPos(ulong uIndex) = 0;
			virtual void setReadPosOffset(long uOffset, bool bForward = true) = 0;
			//virtual void setReadPosAtBegin()										= 0;
			//virtual void setReadPosAtEnd()											= 0;
			virtual void setWritePos(ulong uIndex) = 0;
			virtual void setWritePosOffset(long uOffset, bool bForward = true) = 0;
			virtual void setWritePosAtBegin() = 0;
			virtual void setWritePosAtEnd() = 0;
			virtual ulong getReadPos() const = 0;
			virtual ulong getWritePos() const = 0;
			virtual bool saveAs(const String& strFile) = 0;

		public:
			virtual void encryption();
			virtual void decryption();
			virtual void encryption(ulong uIndex, ulong uCount);
			virtual void decryption(ulong uIndex, ulong uCount);

		};

		/*-----------------------------------------------------------
		class FileIOBase
		------------------------------------------------------------*/
		class FileIOBase : public IFileIO
		{
		public:
			virtual ~FileIOBase();
			FileIOBase& operator = (const FileIOBase& other);

			void setMode(const EFileMode& eMode);
			const EFileMode& getMode() const;
			bool isOpen() const;
			virtual bool readPage(String &strPage, ulong* curSeek = NULL);
			virtual bool writePage(const String& strPage, ulong* curSeek = NULL);
			virtual void resetPageSeek(ulong uSeek = 0);
			virtual bool insert(const String& strInsert, ulong uIndex);
			virtual bool remove(ulong uIndex, ulong uCount, String* strRemoved = NULL);
			virtual bool clearText();

		protected:
			FileIOBase();
			FileIOBase(const FileIOBase& other);

		private:
			void copyOther(const FileIOBase& other);

		protected://private:
			EFileMode	meMode;
			bool		mbOpen;
			ulong		muPageSize;
			ulong		muPageSeek;

		protected:
			String		mstrFile;
		};

		/*-----------------------------------------------------------
		class FileIO
		------------------------------------------------------------*/
		class FileIO : public FileIOBase
		{
		private:
			FILE *m_pFile;

		protected:

		public:
			FileIO();
			virtual ~FileIO();

			virtual bool create();
			virtual void destroy();

			//
			FileIO(const FileIO& f);
			bool operator< (const FileIO& f);
			bool operator==(const FileIO& f);
			FileIO& operator= (FileIO& f);
			FileIO&  operator++();
			FileIO&  operator++(int);
			FileIO&  operator--();
			FileIO&  operator--(int);

			virtual bool open(const String& strPathFile, const EFileMode& eMode);
			virtual void close();
			virtual bool read(String &strRead) const;
			virtual bool read(String &strRead, ulong uSize, ulong uFrom = 0) const;
			virtual bool write(const String& strWrite);
			virtual void  writeEnter();
			virtual void flush();
			virtual ulong getSize() const;
			virtual void setReadPos(ulong uIndex);
			virtual void setReadPosOffset(long uOffset, bool bForward = true);
			virtual void setWritePos(ulong uIndex);
			virtual void setWritePosOffset(long uOffset, bool bForward = true);
			virtual void setWritePosAtBegin();
			virtual void setWritePosAtEnd();
			virtual ulong getReadPos() const;
			virtual ulong getWritePos() const;
			virtual bool saveAs(const String& strFile);
		};

		/*-----------------------------------------------------------
		class Blob
		------------------------------------------------------------*/
		struct Blob
		{
			byte*	ptr = nullptr;
			ulong	size = 0;

			Blob():ptr(nullptr),size(0) {}
			~Blob() { ptr = nullptr; size = 0; }
			void destroy() { delptr(ptr); size = 0; }
		};

		/*-----------------------------------------------------------
		class FileStream
		------------------------------------------------------------*/
		class FileStream : public FileIOBase
		{
		public:
			FileStream();
			FileStream(const String& strFile, const EFileMode& eMode = EFileMode::File_Mode_Read);
			virtual ~FileStream();

			virtual bool open(const String& strFile, const EFileMode& eMode);
			virtual void close();
			virtual bool read(String &strRead) const;
			virtual bool read(String &strRead, ulong uSize, ulong uFrom = 0) const;
			virtual bool write(const String& strWrite);
			virtual void writeEnter();
			virtual void flush();
			Blob getBlob() const;
			ulong getSize() const;
			void setReadPos(ulong uIndex);
			void setReadPosOffset(long uOffset, bool bForward = true);
			void setWritePos(ulong uIndex);
			void setWritePosOffset(long uOffset, bool bForward = true);
			virtual void setWritePosAtBegin();
			virtual void setWritePosAtEnd();
			ulong getReadPos() const;
			ulong getWritePos() const;
			bool saveAs(const String& strFile);

			void readLine(String& strRead, ulong uSize);
			void readLine(String& strRead, const String& strDelimit);

		public:
			static Blob loadFile(const std::string& strFile);

		protected:

		private:
			void doDestroy() override;

		private:
			std::fstream*	mpStream;
		
		};

		/*-----------------------------------------------------------
		class Log
		------------------------------------------------------------*/
		class Log : public IRoot//ILog
		{
		public:
			enum ELogPlace
			{
				Log_Console,
				Log_DebugOutput,
				Log_File,
				Log_UI,
				Log_ALL,
				Log_Max
			};
			enum ETimeType
			{
				Time_None,
				Time_System,
				Time_Elapse,
				Time_Max
			};

			Log();

		public:
			virtual ~Log();
			static Log* singleton();
			static void destroyStatic();

			void open();
			void close();
			Log* crateSubLogger(const String& strLogName);
			void write(const String& strMsg, bool bOnlyForDebug = true, const ETimeType& eTime = Log::ETimeType::Time_Elapse);
			void writeLine();
			//static void sShow(char* szMsg, ...);
			//static void sShow(const ELogPlace& eLog, char* szMsg, ...);
			void setLogFilePath(const String& strLogFilePath);
			const String& getLogFilePath() const;
			void flush();

		private:
			virtual bool doCreate(void* pData = NULL) override;
			virtual void doDestroy() override;
			void showMsgOnConsole(const String& strMsg);
			//void allocConsole(const String& strTitle = "");

		private:
			String					mstrLogFilePath;
			FileStream				mIOStream;
			TMap<String, Log*>*		mpLogMap;
			//
			bool					mbAllocConsole;
		};

		//
#ifndef gLog
#define gLog Log::singleton()
#endif


	}
}