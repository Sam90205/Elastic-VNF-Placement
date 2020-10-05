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
#include <ctime> 
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
    vector<clock_t>countertimes;
    int result=0;
    ofstream UpdateTimeout ("UpdateTimeout.txt");
    for (int aa = 0; aa < 30; aa++)
    {
    ofstream FlowData ("FlowData.txt");
    clock_t a,b;
    int    k, l, h , x ,y, z;
    string o;
    vector<int>oldnode,newnode,Nodenumber;
    vector<vector<int>>oldflow,newflow;
    bool repeat =false; int repeatcounter =0;
    srand(time(NULL) );
    /* 指定亂數範圍 */
    int Corenumber = 12  ;
    int Aggnumber  = 22  ; 
    int Accnumber  = 66  ; 
    int flownumber = 1000 ;
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
    FlowData<<"Old Flow"<<endl;
    for (int i = 0; i < oldflow.size(); i++)
    {
        for (int j = 0; j < oldflow[i].size(); j++)
        {
            FlowData<<oldflow[i][j]<<" ";
        }
        FlowData <<endl;
        for (int j = 0; j < newflow[i].size(); j++)
        {
           FlowData<<newflow[i][j]<<" ";
        }
        FlowData<<endl;
    }
    b=clock();
    ///segment-------------
    vector<int>oldsegmentnode,newsegmentnode;
    vector<vector<int>>oldsegment,newsegment;
    vector<vector<vector<int>>>oldtotalsegment,newtotalsegment;
    int  segmentnodecounter =0;
    int  oldnoderecordstart =0;
    int  oldnoderecordEnd   =0;
    int  newnoderecordstart =0;
    int  newnoderecordEnd   =0;
    bool Pushnode           =false;
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
                        newnoderecordstart=newnoderecordEnd;
                        break;
                    }               
                }
            }
        }
        oldtotalsegment.push_back(oldsegment);
        oldsegment.clear();
        newtotalsegment.push_back(newsegment);
        newsegment.clear();
    }
    //cout <<endl;
    vector<int> flowcapacity;
    for (int i = 0; i < flownumber; i++)
    {
        int x = (rand() % 3) + 1 ;
        flowcapacity.push_back(x);
    }
    
    Options options(PROGRAM_NAME);
    try {
        parseArgs(argc, argv, options);
        k = 4;
        l = 10;
        h = 100000;
        o = "dc.txt";

        KAryFatTree topology(k);
        /*cout << "K        : " << k                  << endl;
        cout << "Link Cap.: " << l                  << endl;
        cout << "Host Cap.: " << h                  << endl;
        cout << "# Nodes  : " << topology.nodeNum() << endl;
        cout << "# Hosts  : " << topology.hostNum() << endl;
        cout << "# Edges  : " << topology.edgeNum() << endl;*/

        SubstrateGraph network(topology);
        //FlowGraph      Flowwork(topology);
        
        for (auto n = topology.hostIt(); n != INVALID; ++n) {
            network.capacity(n, h);     
        }//for
        int s=99;
        for (auto n = topology.hostIt(); n != INVALID; ++n,--s) {

            network.capacity(n, h);     
        }//for
        
        for (int i = 0; i < oldtotalsegment.size(); i++)
        {
            for (int j = 0; j < oldtotalsegment[i].size(); j++)
            {
                
                for (int k = 0; k < oldtotalsegment[i][j].size(); k++)
                {
                    //cout <<oldtotalsegment[i][j][k]<<" ";
                    int l=99;
                    for (auto n = topology.hostIt(); n != INVALID; ++n ,l--)
                    {
                        int capacityadjust = network.residual(n);
                        if (capacityadjust <1000)
                        {
                            flowcapacity[i]=0.5;
                        }
                        
                        if (l==oldtotalsegment[i][j][k])
                        {
                         network.allocate(n,flowcapacity[i]);
                        }
                    }
                    
                }
                
            }
            //cout <<endl;
        }
        ///nodeupdate
        for (int i = 0; i < oldflow.size(); i++)
        {
            for (int j = 0; j < oldflow[i].size(); j++)
            {
                int k=99;
                for (auto n = topology.hostIt(); n != INVALID; ++n ,k--)
                {
                    
                    if (k==oldflow[i][j])
                    {
                        network.allocate(n,flowcapacity[i]);
                    }
                }           
            }
        }
        
        for (int i = 0; i < flownumber; i++)
        {
            for (int j = 0; j < newflow[i].size(); j++)
            {
                int k=99;
                for (auto n = topology.hostIt(); n != INVALID; ++n ,k--)
                {
                    if (k==newflow[i][j])
                    {
                        network.allocate(n,flowcapacity[i]);
                    }
                }   
            }
            for (int j = oldflow[i].size()-1; j > 0 ; j--)
            {
                int k=99;
                for (auto n = topology.hostIt(); n != INVALID; ++n ,k--)
                {
                    if (k==oldflow[i][j])
                    {
                        network.release(n,flowcapacity[i]);
                    }
                }   
            }
        }
        
    a=clock(); 
    countertimes.push_back(a);
    cout <<a-b<<endl;
   /* for (int ii = 0; ii < oldtotalsegment[0].size(); ii++)
    {
        for (int jj = 0; jj < oldtotalsegment[0][ii].size(); jj++)
        {
            cout << oldtotalsegment[0][ii][jj]<<" ";
        }
    }
    cout <<endl;
    for (int ii = 0; ii < newtotalsegment[0].size(); ii++)
    {
        for (int jj = 0; jj < newtotalsegment[0][ii].size(); jj++)
        {
            cout << newtotalsegment[0][ii][jj]<<" ";
        }
    }
    */
   //cout <<endl;
    //cout <<(countertimes[aa]- countertimes[aa-1]) <<endl;
    UpdateTimeout<< (countertimes[aa]- countertimes[aa-1]) <<endl;
    
        for (EdgeIt e(network); e != INVALID; ++e ) {
            network.capacity(e, l);
            network.weight  (e, DEF_LINK_WEIGHT);
        }//for
        
        GraphIO::writeGraph(network, o);
        //GraphIO::writeGraph(Flowwork,"flow.txt");
        //cout << "Saved in : '" << o << "!" << endl;
    }//try
    catch(invalid_argument inExc) {
        cerr << inExc.what() << endl;
        exit(-1);
    }//catch
    catch(...) {
        cerr << options.help() << endl;
        exit(-1);
    }//catch
    }
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

