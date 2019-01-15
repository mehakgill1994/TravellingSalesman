#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream fi(argv[1]);
	if (!fi)
	{
		cout << "cant open fi" << endl;
		return -1;
	}

	ofstream fo(argv[2]);
	if (!fo)
	{
		cout << "cant open fo" << endl;
		return -1;
	}

	int m, e, v;
	
	//reading the first value (i.e. the number of datasets) in the input set
	fi >> m;
	
	//check if the input file is empty
	if (m == 0)
	{
		cout << "the file has no dataset";
	}
	else
	{
		for (int j = 1; j <= m; j++)
		{
			//reading the size of vertex and edge set
			fi >> v;
			fi >> e;
			if (v == 0)
			{
				fo << "Vertex set cannot be null" << endl;
			}
			else if(e == 0)
			{
				fo << "the graph is disconnected" << endl; 
			}
			else
			{
				int G[v][v];
				int H[v][v];

				//adjacency matrix representation of graph
				for(int k=0; k<v; k++)
				{
					for(int l=0; l<v; l++)
					{
						G[k][l] = -1;
						H[k][l] = -1;
					}
				}

				//filling the adjacency matrix with distances
				for(int k=0; k<e; k++)
				{
					int u, v, w;
					fi >> u;
					fi >> v;
					fi >> w;
					G[u][v] = w;
					G[v][u] = w;
					H[u][v] = w;
					H[v][u] = w;
				}
					
				//Travelling Salesman Algorithm		
				int result = 0;	
				int iterations = v;
				while(iterations > 0)
				{
					cout<<"iteration: "<<v-iterations<<endl;

					

					if(iterations == v)
					{
						//row minimization
						for(int k=0; k<v; k++)
						{
							//find row minimum
							int rowMinimum = 2147483647;
							for(int l=0; l<v; l++)
							{
								if(G[k][l] != -1)
								{
									rowMinimum = min(rowMinimum, G[k][l]);
								}
							}

							if(rowMinimum == 2147483647)
								rowMinimum = 0;

							//subtracitng row minimum from all elements in row
							for(int l=0; l<v; l++)
							{
								if(G[k][l] != -1)
								{
									G[k][l]-=rowMinimum;
								}
							}

						}

						//column minimization
						for(int l=0; l<v; l++)
						{
							//find col minimum
							int colMinimum = 2147483647;
							for(int k=0; k<v; k++)
							{
								if(G[k][l] != -1)
								{
									colMinimum = min(colMinimum, G[k][l]);
								}
							}

							if(colMinimum == 2147483647)
								colMinimum = 0;

							//subtracitng col minimum from all elements in row
							for(int k=0; k<v; k++)
							{
								if(G[k][l] != -1)
								{
									G[k][l]-=colMinimum;
								}
							}

						}
					}

					
					bool flagr, flagc;
					//checking if every row has atleast 1 zero
					for(int k=0; k<v; k++)
					{
						flagr = false;
						for(int l=0; l<v; l++)
						{
							if(G[k][l] == 0)
							{
								flagr = true;
							}
						}

						//checked till here
						if(flagr == false)
						{
							if(iterations==4)
							cout<<"true at :" <<k<<endl;
							
							//find row minimum
							int rowMinimum = 2147483647;
							for(int l=0; l<v; l++)
							{
								if(G[k][l] != -1)
								{
									rowMinimum = min(rowMinimum, G[k][l]);
								}
							}

							if(rowMinimum == 2147483647)
								rowMinimum = 0;

							//subtracitng row minimum from all elements in row
							for(int l=0; l<v; l++)
							{
								if(G[k][l] != -1)
								{
									G[k][l]-=rowMinimum;
								}
							}
						}
					}

					

					//checking if every row has atleast 1 zero
					for(int l=0; l<v; l++)
					{
						flagc = false;
						for(int k=0; k<v; k++)
						{
							if(G[k][l] == 0)
							{
								flagc = true;
								//if(iterations==4)
								//cout<<"true at :" <<k<<","<<l<<endl;
							}
						}
						if(flagc == false)
						{
							//find col minimum
							int colMinimum = 2147483647;
							for(int k=0; k<v; k++)
							{
								if(G[k][l] != -1)
								{
									colMinimum = min(colMinimum, G[k][l]);
								}
							}

							if(colMinimum == 2147483647)
								colMinimum = 0;

							//subtracitng col minimum from all elements in row
							for(int k=0; k<v; k++)
							{
								if(G[k][l] != -1)
								{
									G[k][l]-=colMinimum;
								}
							}
						}
					}

					//print
					if(iterations == 1) 
					{
						for(int k=0; k<v; k++)
						{
							for(int l=0; l<v; l++)
							{
								cout<<G[k][l]<<" ";          
							}
							cout<<endl;
						}
					}

					//calculating penalties of all 0's
					int penalty, x, y;
					penalty = -1;
					x = -1;
					y = -1;
					for(int k=0; k<v; k++)
					{
						for(int l=0; l<v; l++)
						{
							if(G[k][l] == 0)
							{
								cout<<k<<" "<<l<<endl;
								//row min
								int rowMin = 2147483647;
								for(int p=0; p<v; p++)
								{
									if(G[p][l] != -1 && p!=k)
									{
										rowMin = min(rowMin, G[p][l]);
									}
								}

								if(rowMin == 2147483647)
									rowMin = 0;

								cout<<"row min: "<<rowMin<<endl;
								//col min
								int colMin = 2147483647;
								for(int q=0; q<v; q++)
								{
									if(G[k][q] != -1 && q!=l)
									{
										colMin = min(colMin, G[k][q]);
									}
								}

								if(colMin == 2147483647)
									colMin = 0;
								cout<<"col min: "<<colMin<<endl;

								if(penalty<(rowMin+colMin))
								{
									penalty = rowMin+colMin;
									x = k;
									y = l;
								}
								cout<<"Penalty: "<<x<<","<<y<<" ->"<<penalty<<endl;
							}

						}
					}

					result+=H[x][y];

					//reseting the selected row & column
					for(int p=0; p<v; p++)
					{
						G[p][y] = -1;
						G[x][p] = -1;
					}					
					G[y][x] = -1;


					iterations--;
				}

				//writing the solution to the output file
				fo<<result;
				if(j!=m)
				{
					fo<<endl;
				}
			}
		}
	}

return 1;
}