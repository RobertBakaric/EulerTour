/*
 * EulerTour.cpp
 * 
 * Copyright 2015 Robert Bakaric <rbakaric@irb.hr>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#include<boost/program_options.hpp>

#include<EulerTour.hpp>


namespace po = boost::program_options;
using namespace std;



void PrintAcknowledgements(){

cout <<"***************************************************************************************"<<"\n";
cout <<"                     EulerTour - Euler Tour Tree Representation                        "<<"\n";
cout <<"                                          by                                           "<<"\n";
cout <<"                                    Robert Bakaric                                     "<<"\n\n";
cout <<"CONTACT:                                                                               "<<"\n";
cout <<" Code written and maintained by Robert Bakaric,                                        "<<"\n";
cout <<" email: rbakaric@irb.hr , bakaric@evolbio.mpg.de                                       "<<"\n\n";
cout <<"ACKNOWLEDGEMENT:                                                                       "<<"\n";
cout <<"                                                                                       "<<"\n\n";
cout <<"LICENSE:                                                                               "<<"\n";
cout <<" The program is distributed under the GNU General Public License. You should have      "<<"\n";
cout <<" received a copy of the licence together  with this software. If not, see              "<<"\n";
cout <<" http://www.gnu.org/licenses/                                                          "<<"\n";
cout <<"***************************************************************************************"<<"\n\n\n";
}


template <typename INT, typename CHARA>
po::variables_map SetOptions(INT& argc, CHARA& argv){

    try {
        int opt;
        string version = "1.0";
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "print version information")
            ("input-file,i", po::value< string >(), "input file")
        ;

        po::positional_options_description p;
        p.add("input-file,i", -1);
        
        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).
                  options(desc).positional(p).run(), vm);
        po::notify(vm);
    
        if (vm.count("help")) {
            cout << "Usage: ./program [options]\n\n";
            PrintAcknowledgements();
            cout << desc;
            exit(0);
        }else if (vm.count("version")) {
            cout << "Program version:  " << version << "\n";
            exit(0);
        }
        if (!vm.count("input-file")){
            cout << "Input file is not defined \n";
            exit(0);
        }
        return vm;    
    }
    catch(std::exception& e)
    {
        cout << e.what() << "\n";
        exit(0);
    }    
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    copy(v.begin(), v.end(), ostream_iterator<T>(os, " ")); 
    return os;
}


template <typename Tint>
void ReadGraph(const string & file, vector<Tint>& parent, vector<Tint>& child){
  
  fstream fs;
  fs.open (file.c_str(), ios::in);
  if ( !fs.is_open()){
    cerr << "Cannot open file: "<<file <<"! Line:" << __LINE__<< endl;
    exit(-1);
  }

  int i = 0; 
  while( !fs.eof()) {
    if(child.size() == i){
       child.resize((child.size()+1)*2);
       parent.resize((parent.size()+1)*2);
    }
    fs >> child[i];
    fs >> parent[i++] ;
  }  
 
  parent.resize(i-1);
  child.resize(i-1);
  fs.close();
}



int main (int argc, char** argv){
  
/* Get cmd Options */  
  po::variables_map arg;
  arg = SetOptions(argc,argv);

  string file =  arg["input-file"].as<string>();

  vector<int> parent;
  vector<int> child;

/* Read Graph */  
  ReadGraph(file, parent, child);
  
/* Construct Euler Tour */
  Euler<int> EObject(parent,child);


  vector<int> vec(parent);
  sort( vec.begin(), vec.end() );
  vec.erase( unique( vec.begin(), vec.end() ), vec.end() );
  int start = 0;

  while(1){
    cout << "\nNOTE: Ctrl-c to quit!\n\n";
    cout<< "List of vertices:\n" << vec <<endl;
    cout << "Choose start vertex:";
    cin >> start;  
    EObject.Traverse(start);
 
/* Print results */
    cout << "\n\nEuler Path:\n\n";
    cout << "Depth:\t" << EObject.GetDepthVec() << endl;    
    cout << "\nVertexId:\t" <<  EObject.GetVertexIdVec() << endl;

    EObject.Clean();
  }
  return 0;
}
