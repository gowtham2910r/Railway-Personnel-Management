#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<dos.h>
void control(char*);
void stn_mas();
void pfm_man();
void wrman();
void wrpfm();
void wr_inbox();
void goods_open(int);
void stall_open(int);
void trnann_open(int);
void stall_man();
void trnann_man();
void goods_man();
void cln_man();
void porter_man();
void porter_open(int);
void cater_open(int);
void food_n_cater();
void view_status(FILE*);
void change_wage(FILE*);
void worker_open(FILE*,FILE*,int);
void chef_open(int);
void cleaner_open(int);
int login(char*,char*);
void main(){
      char user[10]={0};
      char pass[10]={0};
      printf("Enter your username\n");
      gets(user);
      printf("Enter password\n");
      char ch='a';
      int i=0;
      while(ch!=13){
            ch = _getch();
            if(ch==13){
                  printf("\n");
                  break;
            }
            else{
                  pass[i]=ch;
                  i++;
                  printf("*");
            }
      }
      int check = login(user,pass);
      if(check==0){
            printf("Username incorrect\n");
            exit(0);
      }
      else if(check==1){
            printf("Logging in...\n");
            delay(3000);
            printf("\n\n");
            control(user);
      }
      else if(check==2){
            printf("Incorrect Password\n");
            exit(0);
      }

}
void control(char *user){
      if(user[0]=='c' && user[1]=='a' && user[2]=='t'){//caterers
            int id = user[6]-48;
            if(user[7]!=0){
                  id=(id*10) + (user[7]-48);
            }
            cater_open(id);
      }
      else if(user[0]=='c' && user[1]=='h' && user[2]=='e'){//chefs
            int id = user[5]-48;
            chef_open(id);
      }
      else if(user[0]=='p' && user[4]=='_'){//porters
            int id = user[5]-48;
            if(user[6]!=0){
                  id=(id*10) + (user[6]-48);
            }
            porter_open(id);
      }
      else if(user[0]=='c' && user[1]=='l' && user[5]=='e'){//cleaner
            int id = user[8]-48;
            cleaner_open(id);
      }
      else if(user[0]=='g' && user[6]!='m'){//goods loader
            int id = user[6]-48;
            goods_open(id);
      }
      else if(user[0]=='t' && user[3]=='a'){//train announcers
            int id = user[7]-48;
            trnann_open(id);
      }
      else if(user[0]=='s' && user[2]=='a' && user[6]!='m'){//stall workers
            int id = user[6]-48;
            stall_open(id);
      }
      else if(user[0]=='w' && user[2]=='_'){//waiting room incharge of each platform
            int id = user[6]-48;
            wrpfm(id);
      }
      else if(user[0]=='p' && user[1]=='f'){//platform managers
            int id = user[7]-48;
            pfm_man(id);
      }
      else if(user[0]=='w' && user[2]=='m'){//waiting room mananger
            wrman();
      }
      else if(user[0]=='p' && user[6]=='_'){//porter manager
            porter_man();
      }
      else if(user[0]=='f'){//food and catering incharge
            food_n_cater();
      }
      else if(user[0]=='c' && user[1]=='l' && user[5]=='_'){//clean manager
            cln_man();
      }
      else if(user[0]=='g' && user[6]=='m'){//goods manager
            goods_man();
      }
      else if(user[0]=='t' && user[3]=='_'){//train announcing manager
            trnann_man();
      }
      else if(user[0]=='s' && user[1]=='t' && user[2]=='n'){//station master
            stn_mas();
      }
}
void stn_mas(){
      int n;
      do{
            printf("1 - Deliver message to Platform Master\n");
            printf("2 - Deliver Message to Waiting Room Manager\n");
            printf("3 - Exit");
            scanf("%d",&n);
            if(n==1){
                  printf("Enter the id of the platform manager\n");
                  int id;
                  scanf("%d",&id);
                  FILE *ptr;
                  ptr = fopen("PFM_Inbox.txt","a");
                  printf("Enter your message with max 50 characters\n");
                  char mess[51]={0};
                  scanf("%*c%[^\n]s",mess);
                  fprintf(ptr," %d %s~",id,mess);
                  printf("Message Sent\n");
                  fclose(ptr);
            }
            else if(n==2){
                  FILE *ptr;
                  ptr = fopen("WRM_Inbox.txt","a");
                  printf("Enter your message with max 50 characters\n");
                  char mess[51]={0};
                  scanf("%*c%[^\n]s",mess);
                  fprintf(ptr," 2 %s~",mess);
                  printf("Message Sent\n");
                  fclose(ptr);
            }
            else if(n!=3){
                  printf("Invalid Option\n");
            }
      }while(n!=3);
}
void pfm_man(int id){
      int n;
      do{
            printf("1 - View Inbox\n");
            printf("2 - Deliver Message to Waiting Room Manager\n");
            printf("3 - Exit\n");

            scanf("%d",&n);
            if(n==1){
                  FILE *ptr;
                  ptr = fopen("PFM_Inbox.txt","r");
                  int receiver;
                  char *mess;
                  while(!feof(ptr)){
                        fscanf(ptr,"%d",&receiver);
                        mess = (char*)calloc(1,sizeof(char));
                        char ch;
                        int i=0;
                        do{
                              ch = fgetc(ptr);
                              if(ch!='~'){
                                    mess[i]=ch;
                                    i++;
                                    mess = (char*)realloc(mess,i+1);
                              }
                        }while(ch!='~');
                        mess[i]=0;
                        if(receiver==id)
                              printf("Message: \"%s\"\n",mess);
                        fgetc(ptr);

                  }
                  fclose(ptr);
            }
            else if(n==2){
                  FILE *ptr;
                  ptr = fopen("WRM_Inbox.txt","a");
                  printf("Enter your message with max 50 characters\n");
                  char mess[51]={0};
                  scanf("%*c%[^\n]s",mess);
                  fprintf(ptr," 2 %s~",mess);
                  printf("Message Sent\n");
                  fclose(ptr);
            }
            else if(n!=3){
                  printf("Invalid Option\n");
            }
      }while(n!=3);
}
void wrman(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Waiting Room Managers of Platforms\n");
            printf("2 - View/Change Daily Wages of Waiting Room Managers of Platforms\n");
            printf("3 - View Inbox\n");
            printf("4 - Deliver message to Waiting Room Manager of Platforms\n");
            printf("5 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("WR_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("WR.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:{
                        FILE *ptr;
                        ptr = fopen("WRM_Inbox.txt","r");
                        int sender;
                        char *mess;
                        while(!feof(ptr)){
                              fscanf(ptr,"%d",&sender);
                              mess = (char*)calloc(1,sizeof(char));
                              char ch;
                              int i=0;
                              do{
                                    ch = fgetc(ptr);
                                    if(ch!='~'){
                                          mess[i]=ch;
                                          i++;
                                          mess = (char*)realloc(mess,i+1);
                                    }

                              }while(ch!='~');
                              mess[i]=0;
                              char send[25]={0};
                              if(sender==1){
                                    strcpy(send,"Station Master");
                              }
                              else if(sender==2){
                                    strcpy(send,"Platform Manager");
                              }
                              //if(stat==0)
                              printf("Message: \"%s\" from %s\n",mess,send);
                              fgetc(ptr);

                        }
                        fclose(ptr);
                        /*ptr=fopen("WRM_Inbox.txt","w");
                        fclose(ptr);*/
                        break;
                  }
                  case 4:{
                        FILE *ptr;
                        char mess[51]={0};
                        ptr = fopen("WR_Inbox.txt","a");
                        if(ptr==NULL)printf("SAD\n");
                        printf("Enter the id of the room manager\n");
                        int id,i=0;
                        scanf("%d",&id);
                        printf("Enter the message terminated with max length 50 characters\n");
                        scanf("%*c%[^\n]s",mess);
                        fprintf(ptr," %d %s~",id,mess);
                        printf("Message Sent\n");

                  }
                  case 5:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=5);
}
void wrpfm(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("WR.txt","r");
      ptr2=fopen("WR_Log.txt","a");
      printf("1 - Update your log\n");
      printf("2 - View Inbox\n");
      int t;
      scanf("%d",&t);
      if(t==1){
            worker_open(ptr,ptr2,id);
      }
      else if(t==2){
            wr_inbox(id);
      }
}
void wr_inbox(int id){
      FILE *ptr;
      ptr = fopen("WR_Inbox.txt","r");
      int receiver;
      char *mess;
      while(!feof(ptr)){
            fscanf(ptr,"%d",&receiver);
            mess = (char*)calloc(1,sizeof(char));
            char ch;
            int i=0;
            do{
                  ch = fgetc(ptr);
                  if(ch!='~'){
                        mess[i]=ch;
                        i++;
                        mess = (char*)realloc(mess,i+1);
                  }
            }while(ch!='~');
            mess[i]=0;
            if(receiver==id)
                  printf("Message: \"%s\"\n",mess);
            fgetc(ptr);
      }
      fclose(ptr);

}
void goods_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Stall.txt","r");
      ptr2=fopen("Stall_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void stall_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Stall.txt","r");
      ptr2=fopen("Stall_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void trnann_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Trnann.txt","r");
      ptr2=fopen("Trnann_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void stall_man(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Stall Workers\n");
            printf("2 - View/Change Daily Wages of Stall Workers\n");
            printf("3 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Stall_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Stall.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=3);
}
void trnann_man(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Train Announcers\n");
            printf("2 - View/Change Daily Wages of Train Announcers\n");
            printf("3 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Trnann_log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Trnann.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=3);
}
void goods_man(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Goods Loaders\n");
            printf("2 - View/Change Daily Wages of Goods Loaders\n");
            printf("3 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Goods_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Goods.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=3);
}
void cln_man(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Cleaners\n");
            printf("2 - View/Change Daily Wages of Cleaners\n");
            printf("3 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Cleaner_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Cleaner.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=3);
}
void porter_man(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Porters\n");
            printf("2 - View/Change Daily Wages of Porters\n");
            printf("3 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Porter_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Porter.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:break;
                  default:printf("Invalid Option\n");
            }
      }while(n!=3);
}
void porter_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Porter.txt","r");
      ptr2=fopen("Porter_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void cleaner_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Cleaner.txt","r");
      ptr2=fopen("Cleaner_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void food_n_cater(){
      int n=1;
      do{
            printf("1 - View Pending Validations of Caterers\n");
            printf("2 - View/Change Daily Wages of Caterers\n");
            printf("3 - View Pending Validations of Chefs\n");
            printf("4 - View/Change Daily Wages of Chefs\n");
            printf("5 - Exit\n");
            scanf("%d",&n);
            switch(n){
                  case 1:{
                        FILE *ptr;
                        ptr = fopen("Cater_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 2:{
                        FILE *ptr;
                        ptr = fopen("Cater.txt","r+");
                        change_wage(ptr);
                        break;

                  }
                  case 3:{
                        FILE *ptr;
                        ptr = fopen("Chef_Log.txt","r+");
                        view_status(ptr);
                        break;
                  }
                  case 4:{
                        FILE *ptr;
                        ptr = fopen("Chef.txt","r+");
                        change_wage(ptr);
                        break;
                  }
                  case 5: break;
                  default:printf("Invalid Option\n");
            }//end of switch
      }while(n!=5);
}
void view_status(FILE *ptr){
      while(!feof(ptr)){
            int id;
            char date[11]={0};
            char stime[6]={0};
            char etime[6]={0};
            char status[4]={0};
            fscanf(ptr,"%d%s%s%s%s",&id,date,stime,etime,status);
            if(strcmp(status,"TBV")==0){
                  int v = 0,check=0;
                  printf("%d %s %s %s %s\n",id,date,stime,etime,status);
                  while(check==0){
                        printf("1-Validate\n2-Make Invalid\n");
                        scanf("%d",&v);
                        if(v==1){
                              fseek(ptr,-3,SEEK_CUR);
                              fputc('V',ptr);
                              fputc('A',ptr);
                              fputc('L',ptr);
                              fseek(ptr,2,SEEK_CUR);
                              check=1;
                        }
                        else if(v==2){
                              fseek(ptr,-3,SEEK_CUR);
                              fputc('I',ptr);
                              fputc('N',ptr);
                              fputc('V',ptr);
                              fseek(ptr,2,SEEK_CUR);
                              check=1;
                        }
                        else{
                              printf("Invlaid option\n");

                        }
                  }//end of while check=0

            }//end of if strcmp

      }//end of while !feof
      fclose(ptr);
}
void change_wage(FILE *ptr){
      int id;
      float wage;
      printf("Id Wage\n");
            while(!feof(ptr)){
                  fscanf(ptr,"%d%f",&id,&wage);
                  printf("%d %0.1f\n",id,wage);
            }
            int change  = 1;
            do{
                  printf("1 - Change Wage\n");
                  printf("2 - Exit\n");
                  scanf("%d",&change);
                  if(change==1){
                        int new_id;
                        float new_wage;
                        printf("Enter id number to change\n");
                        scanf("%d",&new_id);
                        if(id<1 || id >12){
                              printf("Invalid id\n");
                        }
                        else{
                              printf("Enter the new wage\n");
                              scanf("%f",&new_wage);
                              fseek(ptr,0,SEEK_SET);
                              while(!feof(ptr)){
                                    fscanf(ptr,"%d",&id);
                                    if(id==new_id){
                                          fseek(ptr,0,SEEK_CUR);
                                          fprintf(ptr," %0.1f\n",new_wage);
                                          printf("Wage Changed\n");
                                          break;
                                    }
                                    else{
                                          fscanf(ptr,"%f",&wage);
                                    }
                              }//end of while !feof
                        }//end of else correct id
                  }//end of if change = 1
                  else if(change!=2){
                        printf("Invalid option\n");
                  }
            }while(change!=2);
            fclose(ptr);

}
void cater_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Cater.txt","r");
      ptr2 = fopen("Cater_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
void worker_open(FILE *ptr,FILE *ptr2,int id){
      float wage=0.0;
      int check_id = 0;
      float check_wage = 0.0;
      while(!feof(ptr)){
            fscanf(ptr,"%d %f",&check_id,&check_wage);
            if(check_id==id){
                  break;
            }
      }
      wage = check_wage;
      printf("Id:%d  Daily Wage:%0.1f\n",id,wage);
      fclose(ptr);
      int start_hr,start_min,end_hr,end_min;
      l1:
      printf("Enter the start time as hours and minutes\n");
      scanf("%d%d",&start_hr,&start_min);
      if(start_hr>12 || start_min>59 || start_hr<1 || start_min<0){
            printf("Invalid start time\nEnter again\n");
            goto l1;
      }
      l2:
      printf("Enter the end time as hours and minutes\n");
      scanf("%d%d",&end_hr,&end_min);
      if(end_hr>12 || end_min>59 || end_hr<1 || end_min<0){
            printf("Invalid end time\nEnter again\n");
            goto l2;
      }
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      int dd = tm.tm_mday, mm = tm.tm_mon + 1, yy = tm.tm_year + 1900;
      fprintf(ptr2,"%d %d/%d/%d %d:%02d %d:%02d TBV\n",id,dd,mm,yy,start_hr,start_min,end_hr,end_min);
      printf("Your entry has been updated\n");
      fclose(ptr);

}
void chef_open(int id){
      FILE *ptr,*ptr2;
      ptr = fopen("Chef.txt","r");
      ptr2 = fopen("Chef_Log.txt","a");
      worker_open(ptr,ptr2,id);
}
int login(char *u,char *p){
      int x = 0;
      FILE *ptr;
      ptr = fopen("Login.txt","r");
      char us[10]={0};
      char pa[10]={0};
      char *user = &us;
      char *pass = &pa;
      while(!feof(ptr)){
            fscanf(ptr,"%s%s", us, pa);
            if(strcmp(us,u)==0){
                  if(strcmp(pa,p)==0){
                        x=1;
                        break;
                  }
                  else{
                        x=2;
                        break;
                  }
            }
      }
      fclose(ptr);
      return x;
}
