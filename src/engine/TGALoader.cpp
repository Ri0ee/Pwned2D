// <<< Information >>>
// Author:	Jan Krassnigg (Jan@Krassnigg.de)
// >>> Information <<<

#include "TGALoader.h"

#include <stdio.h>
#include <string>

using namespace std;

namespace NS_TGALOADER
{
	IMAGE::IMAGE ()
	{
		m_iImageWidth = 0;
		m_iImageHeight = 0;
		m_iBytesPerPixel = 0;
	}

	bool IMAGE::LoadTGA (string szFile)
	{
		FILE* pFile = fopen (szFile.c_str(), "rb");

		if (!pFile)
			return (false);

		unsigned char ucHeader[18];
		fread (ucHeader, sizeof (unsigned char) * 18, 1, pFile);

		while (ucHeader[0] > 0)
		{
			--ucHeader[0];

			unsigned char temp;
			fread (&temp, sizeof (unsigned char), 1, pFile);
		}

		m_iImageWidth = ucHeader[13] * 256 + ucHeader[12];
		m_iImageHeight = ucHeader[15] * 256 + ucHeader[14];
		m_iBytesPerPixel = ucHeader[16] / 8;

		if ((m_iImageWidth <= 0) || (m_iImageHeight <= 0) || ((m_iBytesPerPixel != 1) && (m_iBytesPerPixel != 3) && (m_iBytesPerPixel != 4)))
		{
			fclose (pFile);
			return (false);
		}

		m_Pixels.resize (m_iImageWidth * m_iImageHeight * 4);

		if (ucHeader[2] == 2)
		{
			LoadUncompressedTGA (pFile);
		}
		else
		if (ucHeader[2] == 10)
		{
			LoadCompressedTGA (pFile);
		}
		else
		{
			fclose (pFile);
			return (false);
		}

		fclose (pFile);
		return (true);
	}

	void IMAGE::LoadUncompressedTGA (FILE* pFile)
	{
		unsigned char ucBuffer[4] = {255, 255, 255, 255};

		unsigned int* pIntPointer = (unsigned int*) &m_Pixels[0];
		unsigned int* pIntBuffer = (unsigned int*) &ucBuffer[0];

		const int iPixelCount	= m_iImageWidth * m_iImageHeight;

		for (int i = 0; i < iPixelCount; ++i)
		{
			fread (ucBuffer, sizeof (unsigned char) * m_iBytesPerPixel, 1, pFile);

			if (m_iBytesPerPixel == 1)
			{
				ucBuffer[1] = ucBuffer[0];
				ucBuffer[2] = ucBuffer[0];
				ucBuffer[3] = ucBuffer[0];
			}

			(*pIntPointer) = (*pIntBuffer);
			++pIntPointer;
		}
	}

	void IMAGE::LoadCompressedTGA (FILE* pFile)
	{
		int iCurrentPixel = 0;
		unsigned char ucBuffer[4] = {255, 255, 255, 255};
		const int iPixelCount = m_iImageWidth * m_iImageHeight;

		unsigned int* pIntPointer = (unsigned int*) &m_Pixels[0];
		unsigned int* pIntBuffer = (unsigned int*) &ucBuffer[0];

		do
		{
			unsigned char ucChunkHeader = 0;

			fread (&ucChunkHeader, sizeof (unsigned char), 1, pFile);

			if (ucChunkHeader < 128)
			{
				ucChunkHeader++;

				for (int i = 0; i < (int) ucChunkHeader; ++i)
				{
					fread (&ucBuffer[0], m_iBytesPerPixel, 1, pFile);

					if (m_iBytesPerPixel == 1)
					{
						ucBuffer[1] = ucBuffer[0];
						ucBuffer[2] = ucBuffer[0];
						ucBuffer[3] = ucBuffer[0];
					}

					(*pIntPointer) = (*pIntBuffer);

					++pIntPointer;
					++iCurrentPixel;
				}
			}
			else
			{
				ucChunkHeader -= 127;

				fread (&ucBuffer[0], m_iBytesPerPixel, 1, pFile);

				if (m_iBytesPerPixel == 1)
				{
					ucBuffer[1] = ucBuffer[0];
					ucBuffer[2] = ucBuffer[0];
					ucBuffer[3] = ucBuffer[0];
				}

				for (int i = 0; i < (int) ucChunkHeader; ++i)
				{
					(*pIntPointer) = (*pIntBuffer);
					++pIntPointer;

					++iCurrentPixel;
				}
			}
		}
		while (iCurrentPixel < iPixelCount);
	}
}



