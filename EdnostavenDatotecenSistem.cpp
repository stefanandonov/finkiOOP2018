#include<iostream>
#include<cstring>

using namespace std;

class FileAlreadyExists {
	private:
	char name [50];
	
	public:
	FileAlreadyExists(char * name){
		strcpy(this->name,name);
	}
	
	void message() {
		cout<<"File with name "<<name<<" already exists in this folder"<<endl;
	}
};

class FileInformation {
	protected:
	char name [50];
	double size;
	bool r;
	bool w;
	bool x;
	
	public:
	FileInformation(char * name="", double size=0, bool r=false, bool w=false, bool x=false){
		strcpy(this->name,name);
		this->size=size;
		this->r=r;
		this->w=w;
		this->x=x;
	}
    
    FileInformation(const FileInformation &f){
        strcpy(this->name,f.name);
		this->size=f.size;
		this->r=f.r;
		this->w=f.w;
		this->x=f.x;
    }
	
	char * getName() {
		return name;
	}
	
	virtual void printFileInfo() = 0;
	virtual double totalFileMemory() = 0;
	
	bool permissionsAndSize (bool R, bool W, bool X, double s){
        //cout<<(R==r)<<endl;
        //cout<<(W==w)<<endl;
        //cout<<(X==x)<<endl;
        //cout<<(size<s)<<endl;
		if (r==R&&w==W&&x==X && size<=s)
			return true;
		else 
			return false;
	}
};

class File : public FileInformation {
	public:
	File(char * name="", double size=0, bool r=false, bool w=false, bool x=false):
	FileInformation(name,size,r,w,x){
        
    }
	
	File (const File &file){
		strcpy(this->name,file.name);
		this->size=file.size;
		this->r=file.r;
		this->w=file.w;
		this->x=file.x;
		
	}
	
	void printFileInfo() {
		
		if (r)
			cout<<"-r";
		else cout<<"--";
		if (w)
			cout<<"w";
		else cout<<"-";
		if (x)
			cout<<"x ";
		else cout<<"- ";
		
		cout<<name<<" "<<size<<endl;
		
	}
	
	double totalFileMemory() {
		return size;
	}
	
	bool sameName (File &f){
		if (strcmp(this->name,f.name)==0)
			return true;
		else 
			return false;
	}
};

bool operator > (FileInformation & f1, FileInformation &f2){
	return f1.totalFileMemory() > f2.totalFileMemory();
}

class Folder : public FileInformation {
	private:
	File * files;
	int n;
	
	public:
	Folder (char * name, bool read, bool write, bool execute)
	: FileInformation(name,0,read,write,execute) {
		files = new File [0];
		n = 0;
	}
	
	Folder &operator += (File &f){
		for (int i=0;i<n;i++)
			if (files[i].sameName(f))
				throw FileAlreadyExists(files[i].getName());
			
		File * tmp = new File[n+1];
		for (int i=0;i<n;i++)
			tmp[i]=files[i];
		tmp[n++]=f;
		size+=f.totalFileMemory();
		delete [] files;
		files = tmp;
		
		return *this;
	}
	
	void printFileInfo() {
		cout<<"d";
		if (r)
			cout<<"r";
		else cout<<"-";
		if (w)
			cout<<"w";
		else cout<<"-";
		if (x)
			cout<<"x ";
		else cout<<"- ";
		
		cout<<name<<" "<<size<<endl;
		
		for (int i=0;i<n;i++){
			cout<<" ";
			files[i].printFileInfo();
		}
	}
	
	double totalFileMemory() {
		return size;
	}	
	
	File * getFiles() {
		return files;
	}
	
	int getNumber() {
		return n;
	}
};


class FileSystem {
	public:
	
	static void printFileSystem(FileInformation ** fi, int n){
		for (int i=0;i<n;i++)
			fi[i]->printFileInfo();
	} 
	
	static void printFileWithMaxSize(FileInformation **fi, int n){
		FileInformation * max = fi[0];
		//int idx=0;
		for (int i=1;i<n;i++){
			if ((*fi[i])>(*max))
				max=fi[i];
		}
		
		max->printFileInfo();
		
	}
	
	static void printFilesLessThanWithPermissions(FileInformation **fi, int n, bool r, bool w, bool x, double size){
		
		for (int i=0;i<n;i++){
			File * ff = dynamic_cast<File *>(fi[i]);
			if (ff!=0){ //obicna datoteka
                //ff->printFileInfo();
                //cout<<" "<<ff->permissionsAndSize(r,w,x,size)<<endl;
				if (ff->permissionsAndSize(r,w,x,size))
					ff->printFileInfo();
			}
			else { //direktorium
				Folder * folder = dynamic_cast<Folder *>(fi[i]);
				File * files = folder->getFiles();
				int N = folder->getNumber();
				for (int j=0;j<N;j++){
					if (files[j].permissionsAndSize(r,w,x,size)){
						files[j].printFileInfo();
					}
				}
			}
		}
	}
};

int main() {
	
	
	int n; 
	cin>>n;
	FileInformation ** fi = new FileInformation * [n];
	
	for (int i=0;i<n;i++){
		char name [50];
		bool read, write, execute;
		double size;
		int type;
		
		cin>>type;
		if (type==1) { //File
			cin>>name>>size>>read>>write>>execute;
			fi[i] = new File(name,size,read,write,execute);
		}
		else { //Folder
			cin>>name>>read>>write>>execute;
			fi[i] = new Folder(name,read,write,execute);
			int N;
            cin>>N;
			for (int j=0;j<N;j++){
                //cin>>N;
				cin>>name>>size>>read>>write>>execute;
				File f = File(name,size,read,write,execute);
                Folder * folder = dynamic_cast<Folder *>(fi[i]);
                try{
				(*folder)+=f;
                }
                catch (FileAlreadyExists &e){
                    e.message();
                }
			}
		}
	}
	
    cout<<"===TESTING printFileSystem()==="<<endl;
	FileSystem::printFileSystem(fi,n);
    cout<<"===TESTING printFileWithMaxSize()==="<<endl;
    FileSystem::printFileWithMaxSize(fi,n);
    cout<<"===TESTING printFilesLessThanWithPermissions()==="<<endl;
    FileSystem::printFilesLessThanWithPermissions(fi,n,1,1,1,20.5);
	return 0;
}