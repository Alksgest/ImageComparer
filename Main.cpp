#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

int main()
{
	const char* hardcodedPath1 = "C:\\Users\\Vladyslav Kyrychenko\\Desktop\\imageForCompare\\1.JPG";
	const char* hardcodedPath2 = "C:\\Users\\Vladyslav Kyrychenko\\Desktop\\imageForCompare\\2.JPG";
	const char* hardcodedPath3 = "C:\\Users\\Vladyslav Kyrychenko\\Desktop\\imageForCompare\\result.jpg";

	std::function<int()> f = [&hardcodedPath1, &hardcodedPath2, &hardcodedPath3]()
	{
		std::cout << "Work has started!" << std::endl;

		int width1, height1, bpp1;
		int width2, height2, bpp2;

		unsigned char* rgb1 = stbi_load(hardcodedPath1, &width1, &height1, &bpp1, 0);
		unsigned char* rgb2 = stbi_load(hardcodedPath2, &width2, &height2, &bpp2, 0);
		unsigned char* comparedImage = nullptr;
		unsigned int* rgb1Int = nullptr;
		unsigned int* rgb2Int = nullptr;
		unsigned int* rgb3Int = nullptr;
		if (rgb1 == nullptr || rgb2 == nullptr) return -1;
		else
		{
			rgb1Int = new unsigned int[width1 * height1 * bpp1 / 4];
			rgb2Int = new unsigned int[width2 * height2 * bpp2 / 4];

			rgb3Int = new unsigned int[width1 * height1 * bpp1 / 4];

			comparedImage = new unsigned char[width1 * height1 * bpp1];

			int enumerator = 0;
			//for (int i = 0; i < width1 * height1 * bpp1; i += 4)
			//{
			//	++enumerator;
			//	rgb1Int[enumerator] = (rgb1[i] << 24) | (rgb1[i + 1] << 16) | (rgb1[i + 2]) << 8 | (rgb1[i + 3]);

			//}

			//enumerator = 0;
			//for (int i = 0; i < width2 * height2 * bpp2; i += 4)
			//{
			//	++enumerator;
			//	rgb2Int[enumerator] = (rgb2[i] << 24) | (rgb2[i + 1] << 16) | (rgb2[i + 2] << 8) | (rgb2[i + 3]);
			//}
			//for (int i = 0; i < width1 * height1 * bpp1 / 4; ++i)
			//{
			//	if ((rgb1Int[i] ^ rgb2Int[i]))
			//		rgb3Int[i] = rgb1Int[i];
			//	else
			//		rgb3Int[i] = 0;
			//}

			for (int i = 0; i < width1 * height1 * bpp1; i += 4)
			{
				if ((rgb1[i] << 24) | (rgb1[i + 1] << 16) | (rgb1[i + 2]) << 8 | (rgb1[i + 3]) ^
					(rgb2[i] << 24) | (rgb2[i + 1] << 16) | (rgb2[i + 2] << 8) | (rgb2[i + 3]))
				{
					comparedImage[i] = (rgb1[i] << 24) & 0xFF;
					comparedImage[i - 1] = (rgb1[i + 1] << 16) & 0xFF;
					comparedImage[i - 2] = ((rgb1[i + 2]) << 8) & 0xFF;
					comparedImage[i - 3] = (rgb1[i + 3]) & 0xFF;
				}
			}
		}
		//int num = 0;
		//for(int i = 0 ; i < width1 * height1 * bpp1 / 4; ++i)
		//{
		//	comparedImage[num + 1] = (rgb3Int[i] >> 24) & 0xFF;
		//	comparedImage[num + 2] = (rgb3Int[i] >> 16) & 0xFF;
		//	comparedImage[num + 3] = (rgb3Int[i] >> 8) & 0xFF;
		//	comparedImage[num + 4] = (rgb3Int[i]) & 0xFF;
		//	num += 4;
		//}


		int result = stbi_write_jpg(hardcodedPath3, width1, height1, bpp1, comparedImage, 100);

		stbi_image_free(rgb1);
		stbi_image_free(rgb2);
		//stbi_image_free(comparedImage);

		std::cout << "Work has finished!" << std::endl;
		return 0;
	};

	std::thread th(f);

	for (int i = 0; i < 20; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "Main thread working..." << std::endl;
	}

	th.join();

	system("pause");
	return 0;
}