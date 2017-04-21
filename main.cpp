/**
    Weighted Index
    Copyright (C) 2016 Carl Barton, Tomasz Kociumak, Chang Liu, Solon P. Pissis and Jakub Radoszewski.
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#include <iostream>
#include <string>
#include <chrono>
#include <list>
#include <cstdlib>
#include <ctime>
#include <set>

#include "node.h"
#include "defs.h"

using namespace std;
using get_time = chrono::steady_clock;

double ** text;

int main (int argc, char ** argv )
{
	TSwitch sw;
	int mod;
	string text_file;
	string pattern_file;
	string output_file;
	double z;
	
	int n;
	unsigned int k;

	/* Decodes the arguments */

	k = decode_switches ( argc, argv, &sw );

	/* Check the arguments */
	if ( k < 3 )
	{
		usage();
		return 1;
	}
	else
	{
		if ( sw.text_file_name.empty() )
		{
			cout << "Error: No Text input!\n";
			return 0;
		}
		else
		{
			text_file = sw.text_file_name;
		}

/*
		if ( sw.pattern_file_name.empty() )
		{
			cout << "Error: No pattern input!\n";
			return 0;
		}
		else
		{
			pattern_file = sw.pattern_file_name;
		}
*/
		if ( sw.z > 0 )
		{
			z = sw.z;
		}
		else
		{
			cout << "Error: z must be a positive number!\n";
			return 0;
		}

	}
	mod = 0;

	/* read input */
	if ( !read ( text_file, &text, &n ) )
	{
		cout << "Error: Failed to read input!\n";
		return 0;
	}
	cout << "text length:" << n << endl;
	cout << "Finish reading input" << endl;

	auto begin = get_time::now();
	cout << "index begin" << endl;

	string sq;
	weighted_index_building ( text, n, z, &sq );

	int N = sq.size();
//	int * ME = new int [N];
//	MaximalSolidFactors ( text, sq, N, n, z, ME );

	auto end = get_time::now();
	auto diff = end - begin;
	cout << "time:" << chrono::duration_cast<chrono::milliseconds>(diff).count() << " ms "<< endl;
	cout << sq << endl;
	for ( int i = 0; i < n; i++ )
		delete[] text[i];
	delete[] text;

	return 0;
}

