#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include "task1_schema_generated.h"

using namespace Example;

int main()
{
  flatbuffers::FlatBufferBuilder builder1;
  flatbuffers::FlatBufferBuilder builder2;

  // Create Person
  auto name = builder1.CreateString("Ram");
  uint8_t age = 21;
  float weight = 76.5f;
  auto gender = builder1.CreateString("male"); // Convert string to Offset<String>
  auto person = CreatePerson(builder1, name, age, weight, gender);

  // Create Group
  auto group_name = builder2.CreateString("FightClub");
  float average_age = 24.5f;
  float average_weight = 66.0f;
  std::vector<flatbuffers::Offset<flatbuffers::String>> members_vector;
  members_vector.push_back(builder2.CreateString("Ram"));
  members_vector.push_back(builder2.CreateString("Shayam"));
  members_vector.push_back(builder2.CreateString("Raghuveer"));
  auto members = builder2.CreateVector(members_vector);
  auto group = CreateGroup(builder2, group_name, average_age, average_weight, members);

  // Create Client
  auto client1 = CreateClient(builder1, Example::ClientData::ClientData_Person, person.Union());
  auto client2 = CreateClient(builder2, Example::ClientData::ClientData_Group, group.Union());

  std::vector<flatbuffers::Offset<Client>> client_datas;
  client_datas.push_back(CreateClient(builder1, Example::ClientData::ClientData_Person, person.Union()));
  client_datas.push_back(CreateClient(builder2, Example::ClientData::ClientData_Group, group.Union()));
    
  // Finish building
  builder1.FinishSizePrefixed(client1);
  builder2.FinishSizePrefixed(client2);

  // Dump flatbuffer binary
  const uint8_t *buffer1 = builder1.GetBufferPointer();
  const uint8_t *buffer2 = builder2.GetBufferPointer();

  const int size1 = builder1.GetSize();
  const int size2 = builder2.GetSize();
  
  std::cout << "Encoded data size: " << size1 << " bytes\n";
  std::cout << "Encoded data size: " << size2 << " bytes\n";
  
  for (int i = 0; i < size1; i++)
  {
    std::cout << std::hex << static_cast<int>(buffer1[i]) << " ";
  }
  for(int i=0; i <size2; i++)
  {
    std::cout << std::hex << static_cast<int>(buffer2[i]) << " ";
  }
  std::cout << std::endl;
  
  // Save to file
  std::ofstream file("../flatbuffertask/fb_bytes.bin", std::ios::binary); 
  file.write(reinterpret_cast<const char *>(buffer1), size1);
  file.write(reinterpret_cast<const char *>(buffer2), size2);
  file.close();

  return 0;
}