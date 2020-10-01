//
//  main.cpp
//  DataCenterTopo
//
//  Created by Milad Ghaznavi on 4/17/15.
//  Copyright (c) 2015 Milad Ghaznavi. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include "cxxopts.hpp"
#include "fattree.h"
#include "graphio.h"
#include "substrategraph.h"

using namespace std;
using namespace cxxopts;

#define PROGRAM_NAME    "dc"
#define K_OPT           "k"
#define L_K_OPT         "kparam"
#define LINK_CAP_OPT    "l"
#define L_LINK_CAP_OPT  "link"
#define HOST_CAP_OPT    "h"
#define L_HOST_CAP_OPT  "host"
#define OUTPUT_OPT      "o"
#define L_OUTPUT_OPT    "output"

//Data center
#define DEF_DC_FILE_NAME "dc.txt"
#define DEF_LINK_WEIGHT  1

void parseArgs(int, char*[], Options&);

void checkArgs(int, int, int, string);

int main(int argc, char * argv[]) {
    int    k, l, h , x ,y, z;
    string o;
    vector<int>oldnode,newnode,StartNode,bridgeNode,EndNode,Nodenumber;
    vector<vector<int>>oldflow,newflow;
    bool repeat =false; int repeatcounter =0;
    srand(time(NULL) );
    /* 指定亂數範圍 */
    int Corenumber = 12  ;
    int Aggnumber  = 22  ; 
    int Accnumber  = 66  ; 
    /* 產生 [min , max] 的整數亂數 */
    /*for (int i = 0; i < 500 ; i++)
    {
       x = rand() % Corenumber +      0    ;  //core:12
       y = rand() % Aggnumber  +      Corenumber   ;  //agg :22
       z = rand() % Accnumber  +      Corenumber + Aggnumber   ;  //acc :66
       StartNode .push_back(x);
       bridgeNode.push_back(y);
       EndNode   .push_back(z);
    }*/
    int flownumber = 2 ;
    for (int j = 0; j < flownumber; j++)
    {
        oldnode.clear();
        int counter = rand() % 5 + 1;
        for (int i = 0; i < counter; i++)
        {
            x = rand() % Corenumber  +      0                        ;   //core:12
            y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
            z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66           
            if (i==0){
                oldnode.push_back(x);
            }
            
            for (int i = 0; i < oldnode.size(); i++)
            { 
                if (x==oldnode[i] || y == oldnode[i] || z == oldnode[i] ){
                    repeat=true;
                }
            }
            while (repeat==true)
            {
                x = rand() % Corenumber  +      0                        ;   //core:12
                y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                for (int i = 0; i < oldnode.size(); i++)
                {
                    if (x==oldnode[i] || y == oldnode[i] || z == oldnode[i] ){
                        repeatcounter +=1;
                    }
                }
                if (repeatcounter==0){
                    repeat =false;
                }
                else
                {
                    repeat = true;
                }
                repeatcounter=0;
            }
            oldnode.push_back(y);
            oldnode.push_back(z);
            x = rand() % Corenumber  +      0                        ;   //core:12
            y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
            z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66

            for (int i = 0; i < oldnode.size(); i++) 
                if (x==oldnode[i] || y == oldnode[i] || z == oldnode[i] )
                    repeat=true;

            while (repeat==true)
            {
                x = rand() % Corenumber  +      0                        ;   //core:12
                y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                for (int i = 0; i < oldnode.size(); i++)
                {
                    if (x==oldnode[i] || y == oldnode[i] || z == oldnode[i] ){
                        repeatcounter +=1;
                    }
                }
                if (repeatcounter==0){
                    repeat =false;
                }
                else
                {
                    repeat = true;
                }
                repeatcounter=0;
            }
            
            oldnode.push_back(y);
            oldnode.push_back(x);
            if (i==counter-1)
            {
                y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                for (int i = 0; i < oldnode.size(); i++)
                    if (y == oldnode[i] || z == oldnode[i] )
                        repeat=true;
                    
                while (repeat==true)
                {
                    y = rand() % Aggnumber   +      Corenumber               ;   //agg :22 
                    z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                    for (int i = 0; i < oldnode.size(); i++)
                        if (y == oldnode[i] || z == oldnode[i] )
                            repeatcounter +=1;
                        
                    if (repeatcounter==0){
                        repeat =false;
                    }
                    else
                    {
                        repeat = true;
                    }
                    repeatcounter=0;
                }

                oldnode.push_back(y);
                oldnode.push_back(z);
            }
        }

        oldflow.push_back(oldnode);
    }
    
    //NewFlowGenerate-------------------------
    int flowcounter=0;
    int counter = rand() % 5 + 1;
    for (int j= 0 ; j<oldflow.size();j++){
        newnode.clear();
        newnode.push_back(oldflow[j][0]);
        for (int i = 0; i < counter; i++)
        {
            
            x = rand() % Corenumber  +      0                        ;   //core:12 
            y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
            z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
            for (int i = 0; i < newnode.size(); i++)
            {
                if (x == newnode[i] ||y == newnode[i] || z == newnode[i] || z == oldflow[j][oldflow[j].size()-1] ){
                        repeat=true;
                }
            }
            while (repeat==true)
            {
                x = rand() % Corenumber  +      0                        ;   //core:12
                y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                for (int i = 0; i < newnode.size(); i++)
                {
                    if (x == newnode[i] || y == newnode[i] || z == newnode[i] || z == oldflow[j][oldflow[j].size()-1] ){
                        repeatcounter +=1;
                    }
                }
                if (repeatcounter==0){
                    repeat =false;
                }
                else
                {
                    repeat = true;
                }
                repeatcounter=0;
            }
            newnode.push_back(y);
            newnode.push_back(z);
            x = rand() % Corenumber  +      0                        ;   //core:12
            y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
            z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
            for (int i = 0; i < newnode.size(); i++)
                    if (x==newnode[i] || y == newnode[i] || z == newnode[i] || z == oldflow[j][oldflow[j].size()-1] )
                        repeat=true;

                while (repeat==true)
                {
                    x = rand() % Corenumber  +      0                        ;   //core:12
                    y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                    z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                    for (int i = 0; i < newnode.size(); i++)
                    {
                        if (x==newnode[i] || y == newnode[i] || z == newnode[i] ){
                            repeatcounter +=1;
                        }
                    }
                    if (repeatcounter==0){
                        repeat =false;
                    }
                    else
                    {
                        repeat = true;
                    }
                    repeatcounter=0;
                }
                newnode.push_back(y);
                newnode.push_back(x);
                x = rand() % Corenumber  +      0                        ;   //core:12
                y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                for (int i = 0; i < newnode.size(); i++)
                    if (x==newnode[i] || y == newnode[i] || z == newnode[i] || z == oldflow[j][oldflow[j].size()-1] )
                        repeat=true;

                while (repeat==true)
                {
                    x = rand() % Corenumber  +      0                        ;   //core:12
                    y = rand() % Aggnumber   +      Corenumber               ;   //agg :22
                    z = rand() % Accnumber   +      Corenumber + Aggnumber   ;   //acc :66
                    for (int i = 0; i < newnode.size(); i++)
                    {
                        if (x==newnode[i] || y == newnode[i] || z == newnode[i] || z == oldflow[j][oldflow[j].size()-1] ){
                            repeatcounter +=1;
                        }
                    }
                    if (repeatcounter==0){
                        repeat =false;
                    }
                    else
                    {
                        repeat = true;
                    }
                    repeatcounter=0;
                }
                if (i == counter-1)
                {
                    newnode.push_back(y);
                }
                
                //newnode.push_back(y);
        }
        newnode.push_back(oldflow[j][oldflow[j].size()-1]);
        newflow.push_back(newnode);
    }

   
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < oldflow[i].size(); j++)
        {
            cout<<oldflow[i][j]<< " ";
        }
        cout<<endl;
        for (int j = 0; j < newflow[i].size(); j++)
        {
            cout<<newflow[i][j]<< " ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    ///segment-------------
    vector<int>oldsegmentnode;
    vector<int>newsegmentnode;
    vector<vector<int>>oldsegment;
    vector<vector<int>>newsegment;
    int segmentnodecounter=0;
    int oldnoderecordstart=0;
    int oldnoderecordEnd  =0;
    int newnoderecordstart=0;
    int newnoderecordEnd  =0;
    bool Pushnode          =false;
    for (int i = 0; i < newflow.size(); i++)
    {
        int linkStartnode  =0;
        for (int j = 0; j < newflow[i].size()-1; j++)
        {
            newsegmentnode.clear();
            newnoderecordstart=newflow[i][j]; //2
            for (int m = j; m < newflow[i].size()-1; m++)
            {
                newnoderecordEnd  =newflow[i][m+1];//12
                //newnoderecordEnd  =newflow[i][j+1];//12
                int linknodecounter=0;

                for (int k = linkStartnode; k < oldflow[i].size(); k++)
                {
                    if (newnoderecordstart==oldflow[i][k])
                    {
                        oldnoderecordstart=oldflow[i][k];
                    }
                    linknodecounter+=1;
                    if (newnoderecordEnd==oldflow[i][k])
                    {
                        oldnoderecordEnd=oldflow[i][k];
                        linkStartnode +=linknodecounter;
                        for (int l = 0; l < oldflow[i].size() ; l++)
                        {
                            if (oldflow[i][l]==newnoderecordstart)
                            {
                                Pushnode=true;
                            }
                            if (Pushnode==true)
                            {
                                oldsegmentnode.push_back(oldflow[i][l]);
                            }
                            if (oldflow[i][l]==newnoderecordEnd)
                            {
                                Pushnode=false;
                            }
                        }
                        oldsegment.push_back(oldsegmentnode);
                        oldsegmentnode.clear();

                        for (int l = 0; l < newflow[i].size() ; l++)
                        {
                            if (newflow[i][l]==newnoderecordstart)
                            {
                                Pushnode=true;
                            }
                            if (Pushnode==true)
                            {
                                newsegmentnode.push_back(newflow[i][l]);
                            }
                            if (newflow[i][l]==newnoderecordEnd)
                            {
                                Pushnode=false;
                            }
                        }
                        newsegment.push_back(newsegmentnode);
                        newsegmentnode.clear();
                        //cout<<newnoderecordstart << " "<<newnoderecordEnd <<endl;
                        newnoderecordstart=newnoderecordEnd;
                        break;
                    }               
                }
                
               
                /*for (int l = 0; l < linknodecounter; l++)
                {
                    newsegmentnode.push_back(newflow[i][linkStartnode]);
                }
                if (newsegmentnode.size()>=2)
                {
                    newsegment.push_back(newsegmentnode);
                }*/
            }
        }
    }
    for (int i = 0; i < oldsegment.size(); i++)
    {
        for (int j = 0; j < oldsegment[i].size(); j++)
        {
             cout<<oldsegment[i][j]<<" " ;
        }
        cout <<endl;
        for (int j = 0; j < newsegment[i].size(); j++)
        {
             cout<<newsegment[i][j]<<" ";
        }
        cout <<endl;
    }
   /* for (int i = 0; i < newsegment.size(); i++)
    {
        for (int j = 0; j < newsegment[i].size(); j++)
        {
             cout<<newsegment[i][j]<<" ";
        }
        cout <<endl;
    }
    */
    //cout<< segmentnodecounter<<endl;
    Options options(PROGRAM_NAME);
    try {
        parseArgs(argc, argv, options);
        k = 4;
        l = 10;
        h = 10;
        o = "dc.txt";

        KAryFatTree topology(k);
        cout << "K        : " << k                  << endl;
        cout << "Link Cap.: " << l                  << endl;
        cout << "Host Cap.: " << h                  << endl;
        cout << "# Nodes  : " << topology.nodeNum() << endl;
        cout << "# Hosts  : " << topology.hostNum() << endl;
        cout << "# Edges  : " << topology.edgeNum() << endl;

        SubstrateGraph network(topology);
        //FlowGraph      Flowwork(topology);
        for (auto n = topology.hostIt(); n != INVALID; ++n) {
            network.capacity(n, h);
           // network.allocate(n, 10);
        }//for
        for (EdgeIt e(network); e != INVALID; ++e ) {
            network.capacity(e, l);
            network.weight  (e, DEF_LINK_WEIGHT);
        }//for
        
        GraphIO::writeGraph(network, o);
        //GraphIO::writeGraph(Flowwork,"flow.txt");
        cout << "Saved in : '" << o << "!" << endl;
    }//try
    catch(invalid_argument inExc) {
        cerr << inExc.what() << endl;
        exit(-1);
    }//catch
    catch(...) {
        cerr << options.help() << endl;
        exit(-1);
    }//catch

    return 0;
}

void parseArgs(int argc, char* argv[], Options& options) {
    options.add_options()
        (K_OPT        "," L_K_OPT       , "K parameter"                      , value<int>())
        (LINK_CAP_OPT "," L_LINK_CAP_OPT, "Link Capacity (in MB)"            , value<int>())
        (HOST_CAP_OPT "," L_HOST_CAP_OPT, "Host Capacity (in Number of CPUs)", value<int>())
        (OUTPUT_OPT   "," L_OUTPUT_OPT  , "Output File (Default is dc.txt)"  , value<string>());
    options.parse(argc, argv);
}




void checkArgs(int k, int l, int h, string o) {
    if (k < 0) {
        stringstream ss;
        ss << "Parameter k cannot be negative";
        throw invalid_argument(ss.str());
    }//if
}

