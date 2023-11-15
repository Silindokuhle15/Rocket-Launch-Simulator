#pragma once
#include <vector>

namespace rc
{
    std::vector<const char*> filenames = {
            "C:/dev/Rocket Launch Simulator/assets/parallax_mountain_pack/parallax_mountain_pack/layers/parallax-mountain-bg.png",
            //"C:/dev/Rocket Launch Simulator/assets/parallax_mountain_pack/parallax_mountain_pack/layers/parallax-mountain-foreground-trees.png",
            //"C:/dev/Rocket Launch Simulator/assets/parallax_mountain_pack/parallax_mountain_pack/layers/parallax-mountain-montain-far.png",
            //"C:/dev/Rocket Launch Simulator/assets/parallax_mountain_pack/parallax_mountain_pack/layers/parallax-mountain-mountains.png",
            //"C:/dev/Rocket Launch Simulator/assets/parallax_mountain_pack/parallax_mountain_pack/layers/parallax-mountain-trees.png"
    };


	std::vector<float> data1 =
	{
		-1.00f, -0.40f, 0,0,
		-0.90f, -0.40f, 1,0,
		-0.90f, +0.60f, 1,1,
		-1.00f, +0.60f, 0,1
	};

	std::vector<float> data2 =
	{
		+0.90f, -0.40f, 0,0,
		+1.00f, -0.40f, 1,0,
		+1.00f, +0.60f, 1,1,
		+0.90f, +0.60f, 0,1
	};
	std::vector<float> data3 =
	{
		-0.50f, -0.50f, 0,0,
		+0.50f, -0.50f, 1,0,
		+0.50f, +0.50f, 1,1,
		-0.50f, +0.50f, 0,1
	};
	std::vector<float> data4 =
	{
		-1.0f, -1.0f, 0, 0,
		+1.0f, -1.0f, 1, 0,
		+1.0f, +1.0f, 1, 1,
		-1.0f, +1.0f, 0, 1
	};

	std::vector<unsigned int> indices1 =
	{
		0, 1, 2,
		2, 3, 0
	};

	std::vector<unsigned int> indices2 =
	{
		0, 1, 2,
		2, 3, 0
		//4, 5, 6,
		//6, 7, 4
	};

	std::vector<unsigned int> indices3 =
	{
		0, 1, 2,
		2, 3, 0
		//8, 9, 10,
		//10, 11, 8

	};
}
