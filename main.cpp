#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>
#include <mutex>

const std::string PICTURES_FOLDER = "Pictures";
const std::string VIDEOS_FOLDER   = "Videos";
const std::string MUSIC_FOLDER    = "Music";
const std::string OTHERS_FOLDER   = "Others";

std::mutex mtx;

void organizePictures(const std::filesystem::path& sourceDir)
{
   std::filesystem::path picturesDir = sourceDir / PICTURES_FOLDER;

   std::filesystem::create_directory(picturesDir);

   for (const auto& file : std::filesystem::directory_iterator(sourceDir))
   {
      if ((file.path().extension() == ".jpg") || (file.path().extension() == ".png"))
      {
         std::lock_guard<std::mutex> lock(mtx);
         std::filesystem::rename(file.path(), picturesDir / file.path().filename());
      }
   }
}


void organizeVideos(const std::filesystem::path& sourceDir)
{
   std::filesystem::path videosDir = sourceDir / VIDEOS_FOLDER;

   std::filesystem::create_directory(videosDir);

   for (const auto& file : std::filesystem::directory_iterator(sourceDir))
   {
      if ((file.path().extension() == ".mp4") || (file.path().extension() == ".avi"))
      {
         std::lock_guard<std::mutex> lock(mtx);
         std::filesystem::rename(file.path(), videosDir / file.path().filename());
      }
   }
}


void organizeMusic(const std::filesystem::path& sourceDir)
{
   std::filesystem::path musicDir = sourceDir / MUSIC_FOLDER;

   std::filesystem::create_directory(musicDir);

   for (const auto& file : std::filesystem::directory_iterator(sourceDir))
   {
      if ((file.path().extension() == ".mp3") || (file.path().extension() == ".wav"))
      {
         std::lock_guard<std::mutex> lock(mtx);
         std::filesystem::rename(file.path(), musicDir / file.path().filename());
      }
   }
}


void organizeOthers(const std::filesystem::path& sourceDir)
{
   std::filesystem::path othersDir = sourceDir / OTHERS_FOLDER;

   std::filesystem::create_directory(othersDir);

   for (const auto& file : std::filesystem::directory_iterator(sourceDir))
   {
      if (file.is_regular_file())
      {
         std::lock_guard<std::mutex> lock(mtx);
         std::filesystem::rename(file.path(), othersDir / file.path().filename());
      }
   }
}


int main()
{
   std::filesystem::path sourceDir = std::filesystem::current_path();   // Use current directory as the source directory

   std::thread t1(organizePictures, sourceDir);
   std::thread t2(organizeVideos, sourceDir);
   std::thread t3(organizeMusic, sourceDir);
   std::thread t4(organizeOthers, sourceDir);

   t1.join();
   t2.join();
   t3.join();
   t4.join();

   std::cout << "Organizing completed successfully!" << std::endl;

   return 0;
}
