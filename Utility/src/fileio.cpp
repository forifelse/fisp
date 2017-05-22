#include "../include/fileio.h"

namespace fisp
{
	namespace utility
	{
		/*-----------------------------------------------------------
		class IFileIO
		------------------------------------------------------------*/
		void IFileIO::encryption()
		{
			encryption(0, getSize());
		}

		void IFileIO::decryption()
		{
			decryption(0, getSize());
		}

		void IFileIO::encryption(ulong uIndex, ulong uCount)
		{
			FASSERT(isOpen() && uIndex >= 0 && uCount > 0 && uIndex + uCount <= getSize());
			ulong uOldR = getReadPos();
			ulong uOldW = getWritePos();
			String strFile;
			setReadPos(uIndex);
			read(strFile, uCount);
			strFile.encryption();
			setWritePos(uIndex);
			write(strFile);
			flush();
			setReadPos(uOldR);
			setWritePos(uOldW);
		}

		void IFileIO::decryption(ulong uIndex, ulong uCount)
		{
			FASSERT(isOpen() && uIndex >= 0 && uCount > 0 && uIndex + uCount <= getSize());
			ulong uOldR = getReadPos();
			ulong uOldW = getWritePos();
			String strFile;
			setReadPos(uIndex);
			read(strFile, uCount);
			strFile.decryption();
			setWritePos(uIndex);
			write(strFile);
			flush();
			setReadPos(uOldR);
			setWritePos(uOldW);
		}

		/*-----------------------------------------------------------
		class FileIOBase
		------------------------------------------------------------*/
		FileIOBase::FileIOBase()
			:mstrFile("")
			, meMode(File_Mode_WriteAppend)
			, mbOpen(false)
			, muPageSize(1024)
			, muPageSeek(0)
		{

		}

		FileIOBase::FileIOBase(const FileIOBase& other)
			:mstrFile("")
			, meMode(File_Mode_WriteAppend)
			, mbOpen(false)
			, muPageSize(1024)
			, muPageSeek(0)
		{
			copyOther(other);
		}

		FileIOBase::~FileIOBase()
		{
			mstrFile.clear();
			meMode = File_Mode_Max;
			mbOpen = false;
		}

		FileIOBase& FileIOBase::operator = (const FileIOBase& other)
		{
			IFileIO::operator = (other);
			copyOther(other);
			return *this;
		}

		void FileIOBase::copyOther(const FileIOBase& other)
		{
			mstrFile = other.mstrFile;
			meMode = other.meMode;
			mbOpen = other.mbOpen;
			muPageSize = other.muPageSize;
			muPageSeek = other.muPageSeek;
		}

		void FileIOBase::setMode(const EFileMode& eMode)
		{
			if (eMode >= 0 && eMode < File_Mode_Max)
			{
				meMode = eMode;
			}
		}

		const EFileMode& FileIOBase::getMode() const
		{
			return meMode;
		}

		bool FileIOBase::isOpen() const
		{
			return mbOpen;
		}

		bool FileIOBase::readPage(String &strPage, ulong* curSeek /* = NULL */)
		{
			bool bOk = false;
			const ulong uSize = getSize();
			const long uReadSize = (uSize >= muPageSeek + muPageSize) ? muPageSize : (uSize - muPageSeek);
			if (uReadSize > 0)
			{
				bOk = read(strPage, uReadSize, muPageSeek);
				if (bOk)
				{
					if (NULL != curSeek)
					{
						*curSeek = muPageSeek;
					}
					muPageSeek += uReadSize;
				}
			}
			if (!bOk)
				muPageSeek = 0;
			return bOk;
		}

		bool FileIOBase::writePage(const String& strPage, ulong* curSeek /* = NULL */)
		{
			//bool bOk = false;
			//bOk = write(strPage);
			//if(bOk)
			//{
			//	if(NULL != curSeek)
			//	{
			//		*curSeek = muPageSeek;
			//	}
			//	muPageSeek += strPage.getSize();
			//}
			//return bOk;
			return false;
		}

		void FileIOBase::resetPageSeek(ulong uSeek /* = 0 */)
		{
			muPageSeek = uSeek;
		}

		bool FileIOBase::insert(const String& strInsert, ulong uIndex)
		{
			//ulong uSize = getSize();
			//FCHECK(!strInsert.isEmpty() && uIndex >= 0 && uIndex < uSize(),false);
			//String strTemp = sGetTempFile(String::sExtractFileName(mstrFile),mstrFile);
			//FileIO io;
			//io.open(strTemp);
			//String strText;
			//io.read(strText);
			//bool bOk = strText.insert(uIndex,strInsert);
			//FCHECK(bOk,false);

			FCHECK(isOpen(), false);
			String strText;
			read(strText);
			bool bOk = strText.insert(uIndex, strInsert);
			clearText();
			FASSERT(isOpen());
			setWritePos(0);
			write(strText);

			return true;
		}

		bool FileIOBase::remove(ulong uIndex, ulong uCount, String* strRemoved /* = NULL */)
		{
			FCHECK(isOpen(), false);
			String strText;
			read(strText);
			bool bOk = strText.remove(uIndex, uCount, strRemoved);
			clearText();
			FASSERT(isOpen());
			setWritePos(0);
			write(strText);

			return true;
		}

		bool FileIOBase::clearText()
		{
			FASSERT(isOpen());
			const String strFile = mstrFile;
			const EFileMode eMode = meMode;
			close();
			if (open(strFile, File_Mode_ReWrite))
				close();
			open(strFile, eMode);
			return true;
		}

		/*-----------------------------------------------------------
		class FileIO
		------------------------------------------------------------*/
		FileIO::FileIO()
			:m_pFile(nullptr)
		{
		}

		FileIO::~FileIO()
		{
			destroy();
		}

		//
		FileIO::FileIO(const FileIO& f)
		{
			//copyOther(f);
		}

		bool FileIO::create()
		{
			return true;
		}

		void FileIO::destroy()
		{
			close();
		}

		// operator
		bool FileIO::operator <(const FileIO& f)
		{
			return true;
		}

		bool FileIO::operator ==(const FileIO& f)
		{
			return (mbOpen == f.mbOpen && m_pFile == f.m_pFile && mstrFile == f.mstrFile);
		}

		FileIO& FileIO::operator =(FileIO& f)
		{
			//copyOther(f);
			return *this;
		}

		FileIO& FileIO::operator ++()
		{
			return *this;
		}

		FileIO& FileIO::operator ++(int)
		{
			return *this;
		}

		FileIO& FileIO::operator --()
		{
			return *this;
		}

		FileIO& FileIO::operator --(int)
		{
			return *this;
		}

		bool FileIO::open(const String& strPathFile, const EFileMode& eMode)
		{
			FASSERT(!strPathFile.isEmpty() && eMode >= 0 && eMode < File_Mode_Max);
			switch (eMode)
			{
			case File_Mode_Read:
				m_pFile = fopen(strPathFile.getChar(), "rb");
				break;

			case File_Mode_Write:
				m_pFile = fopen(strPathFile.getChar(), "wb");
				break;

			case File_Mode_WriteAppend:
				m_pFile = fopen(strPathFile.getChar(), "ab");
				break;

			case File_Mode_WriteATE:
				m_pFile = fopen(strPathFile.getChar(), "ab");
				break;

			case File_Mode_ReWrite:
				m_pFile = fopen(strPathFile.getChar(), "wb");
				break;

			case File_Mode_Binary:
				m_pFile = fopen(strPathFile.getChar(), "r+b");
				break;

			case File_Mode_ReadWrite:
				m_pFile = fopen(strPathFile.getChar(), "r+b");
				break;

			case File_Mode_ReReadWrite:
				m_pFile = fopen(strPathFile.getChar(), "w+b");
				break;


			default:
				FASSERT(0);
			}
			if (NULL != m_pFile)
			{
				mstrFile = strPathFile;
				meMode = eMode;
				mbOpen = true;
				return true;
			}
			mbOpen = false;
			return false;
		}

		void FileIO::close()
		{
			flush();
			if (mbOpen)
				fclose(m_pFile);
			m_pFile = NULL;
			mbOpen = false;
		}

		bool FileIO::read(String &strRead) const
		{
			ulong uSize = getSize();
			return read(strRead, uSize);
		}

		bool FileIO::read(String &strRead, ulong uSize, ulong uFrom /* = 0 */) const
		{
			FASSERT(isOpen() && uSize <= getSize());
			const uint uCount = 1;
			char* szChar = new char[uSize + 1];
			fseek(m_pFile, uFrom, SEEK_SET);
			fread(szChar, uSize, uCount, m_pFile);
			szChar[uSize] = '\0';
			strRead.setString(szChar);
			delete[]szChar;
			szChar = NULL;
			return true;
		}

		bool FileIO::write(const String& strWrite)
		{
			FASSERT(isOpen() && !strWrite.isEmpty());
			const uint uCount = 1;
			fwrite(strWrite.getChar(), strWrite.getSize(), uCount, m_pFile);
			return true;
		}

		void FileIO::writeEnter()
		{
			write("\r\n");
		}

		void FileIO::flush()
		{
			fflush(m_pFile);
		}

		ulong FileIO::getSize() const
		{
			ulong uSize = 0;
			if (mbOpen && NULL != m_pFile)
			{
				fseek(m_pFile, 0L, SEEK_END);
				uSize = ftell(m_pFile);
			}
			return uSize;
		}

		void FileIO::setReadPos(ulong uIndex)
		{
			FASSERT(isOpen());
			fseek(m_pFile, uIndex, SEEK_SET);
		}

		void FileIO::setReadPosOffset(long uOffset, bool bForward /* = true */)
		{
			FASSERT(isOpen());
			uOffset *= (bForward ? 1 : -1);
			fseek(m_pFile, uOffset, SEEK_CUR);
		}

		void FileIO::setWritePos(ulong uIndex)
		{
			FASSERT(isOpen());
			fseek(m_pFile, uIndex, SEEK_SET);
		}

		void FileIO::setWritePosOffset(long uOffset, bool bForward /* = true */)
		{
			FASSERT(isOpen());
			uOffset *= (bForward ? 1 : -1);
			fseek(m_pFile, uOffset, SEEK_CUR);
		}

		void FileIO::setWritePosAtBegin()
		{
			setWritePos(0);
		}

		void FileIO::setWritePosAtEnd()
		{
			setWritePos(getSize());
		}

		ulong FileIO::getReadPos() const
		{
			FASSERT(isOpen());
			return ftell(m_pFile);
		}

		ulong FileIO::getWritePos() const
		{
			FASSERT(isOpen());
			return ftell(m_pFile);
		}

		bool FileIO::saveAs(const String& strPathFile)
		{
			FCHECK(isOpen() && !strPathFile.isEmpty(), false);
			FileIO fs;
			if (!fs.open(strPathFile, File_Mode_Write))
				return false;
			// read
			String strWrite;
			//ulong uOldW = getWritePos();
			ulong uOldR = getReadPos();
			setReadPos(0);
			read(strWrite);
			setReadPos(uOldR);
			//setWritePos(uOldW);
			// save
			fs.setWritePos(0);
			fs.write(strWrite);
			fs.close();
			return true;
		}

		/*-----------------------------------------------------------
		class FileStream
		------------------------------------------------------------*/
		Blob FileStream::loadFile(const std::string& strFile)
		{
			Blob blob;
			if (strFile.length() <= 0)
				return blob;
			std::fstream fs;
			fs.open(strFile.c_str(), std::ios::basic_ios::binary | std::ios::basic_ios::in);
			if (!fs.is_open())
				return blob;
			//fs.seekg(0);
			//unsigned long idx = fs.tellg();
			fs.seekg(0, std::ios::end);
			blob.size = (unsigned long)fs.tellg();
			blob.ptr = new byte[blob.size + 1];
			fs.seekg(0);
			fs.read((char*)blob.ptr, blob.size);
			blob.ptr[blob.size] = '\0';

			return blob;
		}

	}
}