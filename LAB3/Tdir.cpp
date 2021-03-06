 #include"Tdir.h"
using namespace std;
 HashTable table;
long getFileSize(const char* strFileName)
{
    FILE * fp = fopen(strFileName, "r");
    if(fp==NULL)exit(1);
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

char *join(char *a, char *b) {  
    char *c = (char *) malloc(strlen(a) + strlen(b) + 2); //局部变量，用malloc申请内存  
    if (c == NULL) exit (1);  
    char *tempc = c; //把首地址存下来  
    while (*a != '\0') {  
        *c++ = *a++;  
    }  
	*c++='/';
    while ((*c++ = *b++) != '\0') {  
        ;  
    }  
    //注意，此时指针c已经指向拼接之后的字符串的结尾'\0' !  
    return tempc;//返回值是局部malloc申请的指针变量，需在函数调用结束后free之  
}  

void listDir(char *path)  //main函数的argv[1] char * 作为 所需要遍历的路径 传参数给listDir   
 {  
         DIR              *pDir ;  //定义一个DIR类的指针
         struct dirent    *ent  ;   //定义一个结构体 dirent的指针，dirent结构体见上
         int               i=0  ;  
         char              childpath[512];  //定义一个字符数组，用来存放读取的路径
		 char* c;
   
         pDir=opendir(path); //  opendir方法打开path目录，并将地址付给pDir指针
         memset(childpath,0,sizeof(childpath)); //将字符数组childpath的数组元素全部置零 

         if(NULL==pDir)
         {
         	cerr<<"PATH : "<<path<<" not exist,exit this function"<<endl;
         	return; 
         	}   
         while((ent=readdir(pDir))!=NULL) //读取pDir打开的目录，并赋值给ent, 同时判断是否目录为空，不为空则执行循环体  
         {                  
                 if(ent->d_type & DT_DIR)  //读取 打开目录的文件类型 并与 DT_DIR进行位与运算操作，即如果读取的d_type类型为DT_DIR (=4 表示读取的为目录)
                 {  
   
                        if(strcmp(ent->d_name,".")==0 || strcmp(ent->d_name,"..")==0)  
                                       //如果读取的d_name为 . 或者.. 表示读取的是当前目录符和上一目录符, 用contiue跳过，不进行下面的输出  
                                 continue;  
   
                         sprintf(childpath,"%s/%s",path,ent->d_name);  //如果非. ..则将 路径 和 文件名d_name 付给childpath, 并在下一行prinf输出
                        
   
                         listDir(childpath);  //递归读取下层的字目录内容， 因为是递归，所以从外往里逐次输出所有目录（路径+目录名），
                                            //然后才在else中由内往外逐次输出所有文件名
   
                 }  
               else  //如果读取的d_type类型不是 DT_DIR, 即读取的不是目录，而是文件，则直接输出 d_name, 即输出文件名
               {
				   
				   c = join(path,ent->d_name);
				   
				   Item *newitem=new Item;
				   //printf("%s",c);
				   newitem->key=c;
				   
				   newitem->size=getFileSize(c);
				   
				   if(!(newitem->fp=fopen(c,"r")))exit(1);
				     //printf("#\n");
				   
				    newitem->md5="";
				    newitem->next=NULL;
				   //printf("*\n");
				  table.insertItem(newitem );

               }
         }  
   
 }  
   
 /*int main(){  
     char path[512];
     cout << "please enter a path:" << endl;
	 cin >> path;
	 listDir(path,);
     return 0;  
 }*/
