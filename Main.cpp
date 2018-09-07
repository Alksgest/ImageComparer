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

		if (rgb1 == nullptr || rgb2 == nullptr) return -1;
		else 
		{
			comparedImage = new unsigned char[width1 * height1 * bpp1];
			for (int i = 0; i < width1 * height1 * 3; ++i)
			{
				if ((rgb1[i] ^ rgb2[i]))
					comparedImage[i] = rgb1[i];
				else
					comparedImage[i] = 0;
			}
		}
		int result = stbi_write_jpg(hardcodedPath3, width1, height1, bpp1, comparedImage, 100);

		stbi_image_free(rgb1);
		stbi_image_free(rgb2);
		stbi_image_free(comparedImage);

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