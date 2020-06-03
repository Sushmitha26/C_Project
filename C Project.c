#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
struct userintern {
	int id;
	int userid;
	int internshipid;
	int batch;
};

struct node {
	int id;
	int userid;
	int internshipid;
	int batch;
	struct node*next;
};

struct intern {
	int id;
	char name[100];
	char des[300];
	char req[300];
	char branch[50];
	int sem;
	int studentsperbatch;
};

struct user	{
    int id;
    char age[5];
    char name[20];
    char collegename[50];
    long long phonenumber;
    char password[50];
    char branch[50];
    char emailid[50];
    int sem;
    char regno[50];
    float cgpa;
    char languages[50];
};

void finalize(struct node*head,int stp) {
	FILE*op;
	int stp1=stp;
	int batch=1001;
	struct node* temp=head;
	temp = head;
    while(temp!= NULL) {
    	if(temp->batch==1) {
			temp->batch=batch;
			stp1--;
			if(stp1==0) {
				stp1=stp;
				batch=batch+1;
			}
        }
        temp = temp->next;  
    }
    temp = head;
    while(temp!= NULL) {
        if(temp->batch==2) {
			temp->batch=batch;
			stp1--;
			if(stp1==0) {
				stp1=stp;
				batch=batch+1;
			}
        }
        temp = temp->next;  
    }
}
void rewrite(struct node*head) {
	struct node*temp;
    FILE *outfile;
    struct userintern t;
    // open file for writing
    outfile = fopen ("userinternship.txt", "w"); 
    // write struct to file
    temp = head;
    while(temp!= NULL) {
        t.id=temp->id;
        t.batch=temp->batch;
        t.internshipid=temp->internshipid;
        t.userid=temp->userid;
        fwrite (&t, sizeof(struct userintern), 1, outfile);
        temp = temp->next;  
   }
    fclose (outfile);
}

void deletenode(struct node **head_ref, int position) {
	int i=0;
    // If linked list is empty
    if (*head_ref == NULL)
    	return;
 
    // Store head node
    struct node* temp = *head_ref;
 
    // If head needs to be removed
    if (position == 0) {
        *head_ref = temp->next;   // Change head
        free(temp);               // free old head
        return;
    }
 
    // Find previous node of the node to be deleted
    for (i=0; temp!=NULL && i<position-1; i++)
         temp = temp->next;
 
    // If position is more than number of ndoes
    if (temp == NULL || temp->next == NULL)
         return;
 
    // Node temp->next is the node to be deleted
    // Store pointer to the next of node to be deleted
    struct node *next = temp->next->next;
 
    // Unlink the node from linked list
    free(temp->next);  // Free memory
 
    temp->next = next;  // Unlink the deleted node from list
}

void append(struct node** head_ref, int id,int userid,int internshipid) {
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
 
    struct node *last = *head_ref;  /* used in step 5*/
   
    /* 2. put in the data  */
    new_node->id =id;
	new_node->userid =userid;
    new_node->internshipid =internshipid;
	new_node->batch=-9999;
    /* 3. This new node is going to be the last node, so make next  
          of it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL) {
       *head_ref = new_node;
       return;
    }  
       
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;
   
    /* 6. Change the next of last node */
    last->next = new_node;
    return;    
}

void fcf(int id,struct node* head) {
	FILE *infile;
    FILE *op;
    struct node *temp;
    struct user input;
    struct userintern t;
    // Open person.dat for reading
    infile = fopen ("user.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct user), 1, infile)) {
    	int c=0;
        temp = head;
        while(temp!= NULL) {
		   // Print data of current node
			if((temp->userid==input.id)&&(temp->id==id)) {
		   		printf(" %d: %s\n",input.id,input.name);
		 		temp->batch=1;
   			}
   			else if(temp->id==id) {
				if(temp->batch!=1)
				temp->batch=2;
			}
			else {
			  // deletenode(&head,c);
			}
			c++;
            temp = temp->next;    
    	}
	}
    // close file
    fclose (infile);
}

void branch(char branch[50],int id,struct node*head) {        
	struct node*temp;
	FILE *infile;
    FILE *op;
    struct user input;
    struct userintern t;
    infile = fopen ("user.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct user), 1, infile)) {
    int c=0;
    temp = head;
	    while(temp!= NULL) {
			// Print data of current node
			if((temp->userid==input.id)&&(temp->id==id)&&(strcmp(input.branch,branch)==0)) {
				printf(" %d: %s\n",input.id,input.name);
		    	temp->batch=1;
		   }
			else if(temp->id==id) {
		   		if(temp->batch!=1)
		    	temp->batch=2;
			}
			else {
		  		//deletenode(&head,c);
			}
			c++;
		    temp = temp->next;    
	    }
	}
    fclose (infile);
}
void semester(int idd,struct node*head,int ss) { 
	struct node*temp;
    int i=8;
    int c=0;
	FILE *infile;
	FILE *op;
    struct user input;
    struct userintern t;
    infile = fopen ("user.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct user), 1, infile)) {
        int c=0;
        temp = head;
        while(temp!= NULL) {
        	// Print data of current node
        	if((temp->userid==input.id)&&(temp->id==idd)&&(input.sem==ss)) {
	  			printf(" %d: %s\n",input.id,input.name);
	  			temp->batch=1;
    		}
     		else if(temp->id==idd) {
		    	if(temp->batch!=1)
				temp->batch=2;
			}
			else {
			  //deletenode(&head,c);
			}
			c++;
            temp = temp->next;    
        }
   	}
   	fclose (infile);
}
    
void printcriteria() {
	printf("choice criteria\n");
	printf("1.First in First\n");
	printf("2.based on branch\n");
	printf("3.based on semester\n");
	printf("4.finalise batch\n");
}

void printinternship() {
	FILE *infile;
    struct intern input;
    infile = fopen ("internship.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct intern), 1, infile)) {
    	printf("enter \n");
        printf(" %d: %s\n",input.id,input.name);  
	}
    fclose (infile);
}

void addinternship() {
	FILE *outfile;
	struct intern s;
	while(1) {  
		int n;
		printf(" enter 1 to ADD internship\n");
		printf("emter 2 to exit\n");
		scanf("%d",&n);
		switch(n) {
		case 1:
			printf("Enter id\n");
		    scanf("%d",&s.id);
		    printf("Enter name\n");
		    getchar();
		    gets(s.name);
		    printf("Enter description\n");
		    gets(s.des);
		    printf("Enter requirments\n");
		    gets(s.req);
		    printf("Enter branch\n");
		    gets(s.branch);
		    printf("Enter semester\n");
		    scanf("%d",&s.sem);
		    printf("Enter students per batch\n");
		    scanf("%d",&s.studentsperbatch);
		    // open file for writing
		    outfile = fopen ("internship.txt", "a");
		    if (outfile == NULL) {
		        fprintf(stderr, "\nError opend file\n");
		        exit (1);
		    }
		    // write struct to file
		    fwrite (&s, sizeof(struct intern), 1, outfile);
		    printf("sucessfully added\n");
		    break;
	    case 2:
	    	return ;
		}
	}
	return;
}

void adminmenu() {
	printf("\n1: ADD internship\n");
	printf("2: Create Batch\n");
}

int getinternid(struct intern p) {
	int count=p.id*100+1;
	FILE *fp;
    struct userintern input;  
    // Open person.dat for reading  
    fp = fopen ("userinternship.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct userintern), 1, fp)) {
    	if(p.id==input.id){
    		count++;
		}
	}
	fclose (fp);
    return count;
}

int checkenroled(struct user p) {
	struct userintern data;
	FILE *q;
	q = fopen ("userinternship.txt", "r");
    while(fread(&data, sizeof(struct userintern), 1, q)) {
    	if(data.userid==p.id) {
        	return 0;
		}		
    }
	fclose(q);  
	return 1;
}

struct intern internship(){
	printf("CHOOSE internship\n");
	FILE *infile;
    struct intern input;
    infile = fopen ("internship.txt", "r");
    while(fread(&input, sizeof(struct intern), 1, infile)) {
    	printf("enter \n");
        printf(" %d: %s\n",input.id,input.name);  
	}
    fclose (infile);
    int n;
	printf("enter 1 to see requirments and other details\n");
	scanf("%d",&n);
    infile = fopen ("internship.txt", "r");
    // read file contents till end of file
    while(fread(&input, sizeof(struct intern), 1, infile)) {
        if(input.id==n) {
        	printf("Details:\n NAME:%s\n DESCRIPTION: %s\n REQUIREMENT:%s\n BRANCH: %s\n Semester: %d\n Students per branch :%d\n",input.name,input.des,input.req,input.branch,input.sem,input.studentsperbatch);
  			return input;
			break;
		}  
	}
}

int checkemail(char email[50]) {
	FILE *pp;
	struct user inp;
	pp = fopen ("user.txt", "r");
    // read file contents till end of file
    while(fread(&inp, sizeof(struct user), 1, pp)) {
		if(strcmp(inp.emailid,email)==0) {
			printf("Email address already used \n");
			return 0;
        }
    }
    int c=0,t=0;
    int i=0;
    int len=strlen(email);
    for(i=0;i<=len;i++) {
    	if(email[i]=='@')
        c++;
        if(email[i]=='.')
  			t++;  
    }
    if((c==1)&&(t!=0))
        return 1;
    else
    	return 0;
}

int checkphone(long long p) {
	int c=0;
    while(p!=0) {
        c=c+1;
        p=p/10;
    }
    if(c==10)
        return 1;
    else
        return 0;
}

int checkreg(char regno[50]) {
    int i=0;
    char go[4];
    for(i=0;i<3;i++) {
        go[i]=regno[i];
    }
    go[i]='\0';
    char goo[5][4]={"4NI","1JS","4MH","4VV","4GS"};
    for(i=0;i<5;i++) {
    	if(strcmp(goo[i],go)==0)
    		return 1;
    }
    return 0;
}

int checkbranch(char br[50]) {
    int i=0;
    char brr[5][50]={"computer science","information science","electronic and communication","electrical","electronic and instrumentation"};
	for(i=0;i<5;i++) {
    if(strcmp(brr[i],br)==0)
        return 1;
	}
	return 0;
}

int checkpass(char passw[50]) {
    int i=0;
    int a[4]={0,0,0,0};
    for(i=0;i<=strlen(passw);i++) {
        char c=passw[i];
        if(c>='A'&&c<='Z')
            a[0]++;
        else if(c>='a'&&c<='z')
            a[1]++;
        else if(c>='0'&&c<='9')
            a[2]++;
        else
           a[3]++;
    }
    for(i=0;i<4;i++) {
        if(a[i]<2)
            return 0;
    }
    return 1;
}

int main() {
	printf("-----------------------welcome----------------------------\n");
    printf("1: SignUp\n");
    printf("2: SignIn\n");
    printf("Any other choice: exit\n");
	printf("Enter the choice\n");
	int n,f,ret;
	int co=1;
	char brr[50];
	int semes;
	int spb;
	FILE *bran;
	struct user s;
	FILE *op;
	FILE *print;
	struct node*prin=(struct node*)malloc(sizeof(struct node));
	FILE *t2;
	struct intern br;
	struct userintern data;
	struct user q;
	struct user input;
    struct user p;
	scanf("%d",&n);
	switch(n) {
	case 1:
	    printf("Enter the name\n");
	    scanf("%s",s.name);
	    while(strcmp(s.name," ")==0) {
        	printf("Name can't be empty, re-enter name\n");
        	gets(s.name);
      	}
	    printf("Enter the age\n");
	    scanf("%s",s.age);
	    while((strlen(s.age)>2||strlen(s.age)==0)&&(s.age[0]>'0'&&s.age[0]<='9')) {
        	printf("Age should be numeric\n");
        	scanf("%s",s.age);
    	}
    	printf("Enter the phone number\n");
      	scanf("%lld",&s.phonenumber);
     	while(checkphone(s.phonenumber)==0) {
        	f=checkphone(s.phonenumber);
        	if(f==0) {
            	printf("Phone number should consist of 10 digit only\n");
       		}
    	scanf("%lld",&s.phonenumber);
    	}
	    printf("Enter the email address\n");
	    scanf("%s",s.emailid);
     	f=checkemail(s.emailid);
    	while(f==0) {
	        printf("Invalid email address\n");
	        printf("Enter the email address\n");
	        scanf("%s",s.emailid);
     		f=checkemail(s.emailid);
    	}
	    getchar();
	    printf("Enter college\n");
	    gets(s.collegename);
	    while(strcmp(s.collegename," ")==0) {
       		printf("CollegeName can't be empty, re-enter college name\n");
       		gets(s.collegename);
      	}
     	printf("Enter registration number\n");
     	gets(s.regno);
        while(checkreg(s.regno)==0) {
       		printf("Entered registration number does not belong to list\n");
       		gets(s.regno);
      	}
     	printf("Enter branch\n");
     	gets(s.branch);
    	while(checkbranch(s.branch)==0) {
       		printf("Entered branch does not belong to list\n");
       		gets(s.branch);
      	}
      	printf("Enter semester\n");
      	scanf("%d",&s.sem);
      	while(s.sem>=9){
        	printf("Semester should be less than 8\n");
        	scanf("%d",&s.sem);
      	}
      	getchar();
      	printf("Enter the password\n");
      	gets(s.password);
      	while(checkpass(s.password)==0) {
        	printf("Password must consists of at least 2[A-Z], 2[a-z],2[!@..+*] and 2[0-9] character\n");
        	gets(s.password);
      	}	
      	printf("Confirm password\n");
      	char confipass[50];
      	gets(confipass);
      	while(strcmp(confipass,s.password)!=0) {
          	printf("Password did not match\n");
          	gets(confipass);
      	}	
      	printf("Enter the language known\n");
      	gets(s.languages);
      	printf("Enter CGPA\n");
      	scanf("%f",&s.cgpa);
      	while(s.cgpa>10.0) {
          	printf("cgpa should be less than 10");
          	scanf("%f",&s.cgpa);
      	}
      	FILE *fp;
	    // open file for writing
	    fp = fopen ("user.txt", "a");
	    FILE *count;
     	struct user countt;
     	co=1;
    	// Open person.dat for reading
    	count = fopen ("user.txt", "r");
    	// read file contents till end of file
    	while(fread(&countt, sizeof(struct user), 1, count)) {
        	co++;
		}
    	fclose (count);
	    s.id=co;
	    fwrite (&s, sizeof(struct user), 1, fp);
	    fclose(fp);
	    printf("WELCOME %s\n",s.name);
	 	break;
 
	case 2:
      	printf("Enter the username\n");
      	scanf("%s",p.emailid);
      	if(strcmp(p.emailid,"admin")==0) {
      		printf("Enter password\n");
      		scanf("%s",p.password);
      		while(strcmp(p.password,"admin")!=0) {
		      	printf("Incorrect password !renter the password\n");
		      	scanf("%s",p.password);
      		}
      		printf("WELCOME Admin!");
      		adminmenu();
      		int ch;
      		scanf("%d",&ch);
      		switch(ch) {
      		case 1:
				addinternship();
				break;
	  		case 2:
				printf("Select internship\n");
				printinternship();
				int cho;
				printf("Enter your choice\n");
				scanf("%d",&cho);
				struct node* head = NULL;
				FILE *write;
			   	struct userintern no;
		        // Open person.dat for reading
		        write = fopen ("userinternship.txt", "r");
		        // read file contents till end of file
		        while(fread(&no, sizeof(struct userintern), 1, write))
		        	append(&head,no.id,no.userid,no.internshipid);
		        fclose (write);  
		        while(1) {  
      				printcriteria();
   					int cri;
					printf("Enter your choice\n");
					scanf("%d",&cri);    
					switch(cri) {  
					case 1:
						fcf(cho,head);
						break;
					case 2:
                     	bran= fopen ("internship.txt", "r");
			            while(fread(&br, sizeof(struct intern), 1, bran)) {
				        	if(br.id==cho) {
				                strcpy(brr,br.branch);
				  				break;
							}
			            }
                   		fclose (bran);
						branch(brr,cho,head);
						break;
					case 3:
						printf("Enter the semester\n");
						scanf("%d",&semes);
					 	semester(cho,head,semes);
					 	break;
					case 4:
						bran= fopen ("internship.txt", "r");
                    	while(fread(&br, sizeof(struct intern), 1, bran)) {
			                if(br.id==cho) {
		                      	spb=br.studentsperbatch;
		  						break;
							}
                 		}
                   		fclose (bran);
						finalize(head,spb);
						rewrite(head);
						printf("Batch assigned sucessfully....\n");
						print= fopen ("userinternship.txt", "r");
			            while(fread(prin, sizeof(struct userintern), 1, print)) {
	                		printf("userId %d  Id %d internshipId %d batch %d \n",prin->userid,prin->id,prin->internshipid,prin->batch);
			            }
						return 0;
					}		
            	}
   			}
 		}
 		
      	else {
    		while(1) {
       			op = fopen ("user.txt", "r");
				while(fread(&input, sizeof(struct user), 1, op)) {
					if(strcmp(input.emailid,p.emailid)==0) {
       					printf("Enter password\n");
  						scanf("%s",p.password);
  						while(strcmp(p.password,input.password)!=0) {
     						printf("password did not match, try agin\n");
						  	scanf("%s",p.password);
						}
					  	if(strcmp(p.password,input.password)==0) {
					  		int y=0;
					  		printf("------------WELCOME ---------------\n %s \n",input.name);
							while(y==0) {
							 	struct intern e=internship();
							 	int w;
							  	printf("Enter 1 to confirm \n 2 to go back to menu\n 3 to exit\n");
							  	scanf("%d",&w);
							  	switch(w) {
  								int check;
  								case 1:
								  	check=checkenroled(input);
								  	if(check==0) {
										printf("Sorry you have a pending Internship to complete\n");
								        return 0;
								    }
									data.id=e.id;
									data.userid=input.id;
									data.internshipid=getinternid(e);
						    		t2=fopen("userinternship.txt","a");
						            fwrite (&data, sizeof(struct userintern), 1, t2);
						            printf("welcome, your have opted %s \n",e.name);
						            y=1;
						            return 0;
						            break;
           
            					case 2:
            						y=0;
									break;
								case 3:
									return 0;
 
  								}
    						}
  							return 0;
  						}
					}
    			}
    			fclose(op);
    			printf("username does not exsit \n");
				scanf("%s",p.emailid);
    		}
    	}
		break;
		default:
		printf("Enter a valid input\n");
		break;
	}
	return 0;
}
