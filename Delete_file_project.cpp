#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <windows.h>
#include <memory>
namespace fs = std::filesystem;


class Timer
{
public:
	Timer()
	{
		start = std::chrono::steady_clock::now();
	}
	~Timer()
	{
		end = std::chrono::steady_clock::now();
		std::chrono::duration<float>duration = end - start;
		std::cout << "Потратило времени " << duration << '\n';
	}
private:
	std::chrono::time_point<std::chrono::steady_clock>start, end;
};

int main()
{
	try
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		std::cout << "\t\tЭто программа создана для облегченного удаления файлов если их много!\n";
		std::cout << "--------------------------------------------------------------------------------------------------------------------------\n";
		std::cout << "Ввидите путь, который хотите очистить заменяя слеши на / ";
		std::string path_;
		std::getline(std::cin, path_);
		fs::path path = path_;

		std::cout << "Введи какой формат файла ты хочешь чтобы удалились\n";
		std::string type;
		std::cin >> type;

		std::transform(type.begin(), type.end(), type.begin(), [](unsigned char c) {
			return std::tolower(c);
			});
		Timer timer;
		if (fs::exists(path.string()))
		{
			std::cout << "Такая директория существует начинаю удаление\n\n";
			std::vector<std::shared_ptr<fs::path>>vec;

			for (const auto& i : fs::directory_iterator(path))
			{
				if (i.path().extension() == type)
				{
					vec.push_back(std::make_shared<fs::path>(i.path()));
				}
			}
			std::cout << "Найдено " << vec.size() << " по вашему запросу\n";
			for (const auto& i : vec)
			{
				std::string file = i->filename().string();
				std::cout << file << " удалён" << '\n';
				fs::remove(*i);
			}
			std::cout << "\nВсе файлы " << type << " удалены\n";
		}
		else
		{
			std::cout << "Такой директории не существует\n";
		}
		
		
	}
	catch (const std::exception&ex)
	{
		std::cout << ex.what() << '\n';
	}
	std::cin.ignore(10000, '\n');
	std::cout << "Press Enter to exit...";
	std::cin.get();
	return 0;
}