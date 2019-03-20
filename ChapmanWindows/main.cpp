#include <iostream>
#include <memory>

#include <boost/program_options.hpp>
#include <boost/math/constants/constants.hpp>

#include "scene.h"

auto load_scene_1(size_t max_trace_depth) -> std::shared_ptr<scene>
{
	auto scene = std::make_shared<::scene>(color::WHITE, 0.5, max_trace_depth);

	const auto pi = boost::math::constants::pi<double>();

	const auto number_of_spheres = 90;
	const double radius = 6;
	for (auto i = 0; i < number_of_spheres; ++i)
	{
		const auto angle_factor = 2 * pi / number_of_spheres;

		const auto position_angle = angle_factor * i;
		const auto x = radius * std::cos(position_angle * 4);
		const auto y = 8.0 / number_of_spheres * i - 4;
		const auto z = radius * std::sin(position_angle * 4) - 11;

		const auto angle_offset = pi / 4;
		const auto color_angle = angle_offset + position_angle;
		const auto r = 0.5 + 0.5 * std::cos(color_angle);
		const auto g = 0.5 + 0.5 * std::sin(color_angle * 2);
		const auto b = 0.5 + 0.5 * std::sin(-color_angle) * std::cos(-color_angle);

		const color color(r, g, b);

		const auto ball_material = scene->add_material(color, 1.0, 2.0, 1.0, 0.1);

		scene->add_sphere({ x, y, z }, 0.25, ball_material);
	}

	const auto top_plane = scene->add_material(color::WHITE, 1.0, 0.1, 1.0, 0);
	const auto bottom_plane = scene->add_material(color::WHITE, 1.0, 0.1, 1.0, 1.0);
	scene->add_plane({ 0, 3.5, 0 }, { 0, -1, 0 }, top_plane);
	scene->add_plane({ 0, -3.5, 0 }, { 0, 1, 0 }, bottom_plane);

	scene->add_directional_light({ 1, 0, -0.5 }, color::WHITE, 1.0);
	scene->add_directional_light({ -1, 0, -0.5 }, color::WHITE, 1.0);
	scene->add_point_light({ 0, 2.5, -10 }, color::WHITE, 30);
	scene->add_point_light({ 10, 1, -1 }, color::WHITE, 10);

	return scene;
}

auto load_scene_2(size_t max_trace_depth) -> std::shared_ptr<scene>
{
	auto scene = std::make_shared<::scene>(color::WHITE, 0.1, max_trace_depth);

	const auto pi = boost::math::constants::pi<double>();

	const auto ball_material1 = scene->add_material(color::RED, 0.3, 2.0, 1.0, 0.0);
	const auto ball_material2 = scene->add_material(color::YELLOW, 0.3, 2.0, 1.0, 0.0);
	const auto ball_material3 = scene->add_material(color::MAGENTA, 0.3, 2.0, 1.0, 0.0);
	scene->add_sphere({ -4, 0, -11 }, 2, ball_material1);
	scene->add_sphere({ 0, 0, -11 }, 2, ball_material2);
	scene->add_sphere({ 4, 0, -11 }, 2, ball_material3);

	const auto non_reflective = scene->add_material(color::WHITE, 0.5, 0.1, 1.0, 0.0);
	const auto reflective = scene->add_material(color::WHITE, 0.001, 0.1, 1.0, 1.0);

	scene->add_plane({ 0, -5, 0 }, {0, 1, 0}, reflective);
	scene->add_plane({ 0, 5, 0 }, { 0, -1, 0 }, reflective);
	scene->add_plane({ -5, 0, 0 }, {1, 0, 0}, reflective);
	scene->add_plane({ 5, 0, 0 }, { -1, 0, 0 }, reflective);

	scene->add_point_light({ -4, -4, 0 }, color::WHITE, 30);
	scene->add_point_light({ 4, -4, 0 }, color::WHITE, 30);
	scene->add_point_light({ -4, 4, 0 }, color::WHITE, 30);
	scene->add_point_light({ 4, 4, 0 }, color::WHITE, 30);

	return scene;
}

auto load_scene_3(size_t max_trace_depth) -> std::shared_ptr<scene>
{
	auto scene = std::make_shared<::scene>(color::WHITE, 0.8, max_trace_depth);

	const auto pi = boost::math::constants::pi<double>();

	const auto red_velvet = scene->add_material(color::RED, 1.0, 0.1, 1.0, 0.0);
	const auto blue_velvet = scene->add_material(color::BLUE, 1.0, 0.1, 1.0, 0.0);
	const auto metal = scene->add_material(color::WHITE, 0.2, 1.0, 1.0, 1.0);
	scene->add_sphere({ -7.5, 0, -11 }, 2, red_velvet);
	scene->add_sphere({ 0, 3.5, -11 }, 4, metal);
	scene->add_sphere({ 7.5, 0, -11 }, 2, blue_velvet);

	const auto top_plane = scene->add_material(color::WHITE, 1.0, 0.1, 1.0, 0);
	const auto bottom_plane = scene->add_material(color::WHITE, 1.0, 0.1, 1.0, 0);
	scene->add_plane({ 0, 3.5, 0 }, { 0, -1, 0 }, top_plane);
	scene->add_plane({ 0, -3.5, 0 }, { 0, 1, 0 }, bottom_plane);

	//scene->add_directional_light({ 1, 0, -5 }, color::WHITE, 1.0);
	//scene->add_directional_light({ -1, 0, -5 }, color::WHITE, 1.0);
	scene->add_point_light({ -3, 3, -3 }, color::WHITE, 30);
	scene->add_point_light({  7, 7, 0 }, color::WHITE, 30);

	return scene;
}

auto load_scene_4(size_t max_trace_depth) -> std::shared_ptr<scene>
{
	auto scene = std::make_shared<::scene>(color::WHITE, 0.8, max_trace_depth);

	const auto pi = boost::math::constants::pi<double>();

	const auto number_of_spheres = 90;
	const double radius = 6;
	for (auto i = 0; i < number_of_spheres; ++i)
	{
		const auto angle_factor = 2 * pi / number_of_spheres;

		const auto position_angle = angle_factor * i;
		const auto x = radius * std::cos(position_angle * 4);
		const auto y = 8.0 / number_of_spheres * i - 4;
		const auto z = radius * std::sin(position_angle * 4) - 11;

		const auto angle_offset = pi / 4;
		const auto color_angle = angle_offset + position_angle;
		const auto r = 0.5 + 0.5 * std::cos(color_angle);
		const auto g = 0.5 + 0.5 * std::sin(color_angle * 2);
		const auto b = 0.5 + 0.5 * std::sin(-color_angle) * std::cos(-color_angle);

		const color color(r, g, b);

		const auto ball_material = scene->add_material(color, 1.0, 0.8, 1.0, 0.5);

		scene->add_sphere({ x, y, z }, 0.25, ball_material);
	}

	const auto metal = scene->add_material(color::WHITE, 0.1, 1.0, 1.0, 1.0);
	scene->add_sphere({ 0, 3.5, -11 }, 4, metal);

	const auto top_plane = scene->add_material(color::WHITE, 0.8, 0.1, 1.0, 0);
	const auto bottom_plane = scene->add_material(color::WHITE, 0.8, 0.1, 1.0, 0);
	scene->add_plane({ 0, 3.5, 0 }, { 0, -1, 0 }, top_plane);
	scene->add_plane({ 0, -3.5, 0 }, { 0, 1, 0 }, bottom_plane);

	scene->add_point_light({ -3, 3, -3 }, color::WHITE, 5);
	scene->add_point_light({  3, 3, -3 }, color::WHITE, 5);
	scene->add_point_light({ -3, 3, -18 }, color::WHITE, 5);
	scene->add_point_light({  3, 3, -18 }, color::WHITE, 5);

	return scene;
}

int main(const int argc, const char* argv[])
{
	try
	{
		std::cout << "Chapman v1.0" << std::endl;

		size_t width;
		size_t height;
		size_t max_trace_depth;
		std::string filename;
		boost::program_options::options_description description("Usage");
		description.add_options()
			("width", boost::program_options::value<size_t>(&width)->default_value(3840), "Image width")
			("height", boost::program_options::value<size_t>(&height)->default_value(2160), "Image height")
			("max-trace-depth", boost::program_options::value<size_t>(&max_trace_depth)->default_value(0), "Maximum trace depth")
			("output", boost::program_options::value<std::string>(&filename)->default_value("image.ppm"), "Output filename");
		boost::program_options::variables_map vm;
		store(parse_command_line(argc, argv, description), vm);
		notify(vm);

		std::cout << "Loading scene..." << std::endl;
		const auto scene = load_scene_4(max_trace_depth);

		std::cout << "Rendering " << width << "x" << height << " pixels..." << std::endl;

		auto field_of_view = 90.0;
		const auto camera = std::make_shared<::camera>(vector3(0,0, 0), vector3(0,0,-1), vector3(0, 1, 0), field_of_view);

		const auto image = std::make_shared<::image>(width, height);

		scene->render(camera, image);

		std::cout << "Saving image to " << filename << "..." << std::endl;
		image->write_to_disk(filename, false);

		std::cout << "Done!" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}
