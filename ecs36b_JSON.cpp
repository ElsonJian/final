
// ecs36b_JSON.cpp
// #define _ECS36B_DEBUG_

#include "ecs36b_Common.h"

/*
void
myPrintLog
(std::string content, std::string fname)
{
  if (fname.size() == 0) return;
  
  FILE *log_f = fopen(fname.c_str(), "a");
  if (log_f == NULL) return;
  
  JvTime *jv_ptr = getNowJvTime();
  std::string *str_ptr = jv_ptr->getTimeString();
  std::string *str_ptr = jv_ptr->getTimeString();
  fprintf(log_f, "[%s] %s\n", str_ptr->c_str(), content.c_str());
  delete str_ptr;
  delete jv_ptr;
  fflush(log_f);
  fclose(log_f);
  return;
}
*/
int
myParseJSON
(std::string input, Json::Value * jv_ptr)
{
  if (jv_ptr == NULL) return -1;

  Json::CharReaderBuilder builder;
  Json::CharReader* reader;
  std::string errors;
  bool parsingSuccessful;

  reader = builder.newCharReader();
  parsingSuccessful = reader->parse(input.c_str(),
				    input.c_str() + input.size(),
				    jv_ptr, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the content of the first JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
    return -2;
  }

  return 0;
}

char *
myFile2String
(char *f_name)
{
  if (f_name == NULL) return NULL;
  FILE * f_ptr = fopen(f_name, "r");
  if (f_ptr == NULL) return NULL;

  
  long lSize;
  size_t lresult;

  fseek(f_ptr, 0 , SEEK_END);
  lSize = ftell(f_ptr);
  rewind(f_ptr);

  // allocate memory to contain the whole file:
  char *result_ptr = (char *) malloc(sizeof(char)*lSize);
  // copy the file into the buffer:
  lresult = fread(result_ptr, 1, lSize, f_ptr);
  
  fclose(f_ptr);

  if (lresult != lSize)
    {
      fputs("Reading error", stderr);
      free(result_ptr);
      return NULL;
    }

  return result_ptr;
}

int
myFile2JSON
(char *f_name, Json::Value * jv_ptr)
{

  char *json_str = myFile2String(f_name);
  int rc = myParseJSON(json_str, jv_ptr);
  free(json_str);
  return rc;
}

int
myJSON2File
(char *f_name, Json::Value * jv_ptr)
{
  if (f_name == NULL) return -1;
  if (jv_ptr == NULL) return -2;

  FILE * f_ptr = fopen(f_name, "w");
  if (f_ptr == NULL)
    {
      std::cout << f_name << " fopen for write failed myJSON2File" << std::endl;
      return -3;
    }
  std::string json_str = (*jv_ptr).toStyledString();
  int msize = json_str.size() + 1;
  char *json_buf_ptr = (char *) malloc(msize);
  bzero(json_buf_ptr, msize);
  sprintf(json_buf_ptr, "%s", ((*jv_ptr).toStyledString()).c_str());

  long lSize;
  size_t lresult;

  lSize = strlen(json_buf_ptr);
  //std::cout << f_name << " " << lSize <<  std::endl;
  lresult = fwrite(json_buf_ptr, 1, lSize, f_ptr);
  free(json_buf_ptr);
  fclose(f_ptr);

  if (lresult != lSize)
    {
      fputs("Writing error", stderr);
      return -4;
    }

  return 0;
}
