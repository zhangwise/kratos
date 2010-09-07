// Copyright (C) 2010 Riccardo Rossi, Pooyan Dadvand, Nelson Maireni
// Email contact: rrossi@cimne.upc.edu
// The current tetrahedra splitting library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
	

//input parametrs:
//edges --> int c array of size 6
//t     --> int c array of size 56 (=14*4) -- the first nel*4 positions will be occupied
//nel = number of elements in the subdivision
//output parameters: true->splitting needed    false-->no splitting needed

bool Split(const int* edges, int* t, int* nel, int* splitted_edges, int* nint) {
    *(splitted_edges) = 0;
    for (unsigned int i = 0; i < 6; i++)
        if (edges[i] > 3)
            *splitted_edges = *splitted_edges + 1;

    if (*splitted_edges == 0) {
        //no splitting needed
        *nel = 1;
        t[0] = 0;
        t[1] = 1;
        t[2] = 2;
        t[3] = 3;
        return false;
    }

    //the internal node is normally not needed so by default we set to false
    (*nint) = 0;

    if (edges[0] == 0) {
        if (edges[1] == 0) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 3;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 0;
                            t[15] = 9;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 6;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 6;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 6;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 6;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 6;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 6;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 6;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 0;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 6;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 6;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 0;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
            }
        }
        if (edges[1] == 2) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 9;
                            t[4] = 9;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 0;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 0;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 9;
                            t[4] = 9;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 0;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 0;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 0;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 9;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 9;
                            t[6] = 3;
                            t[7] = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 9;
                            t[4] = 9;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 0;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 0;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 9;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 9;
                            t[6] = 3;
                            t[7] = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 9;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 9;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 7;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 7;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 7;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 0;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 0;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 9;
                            t[4] = 9;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 0;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 0;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 0;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 1;
                            t[7] = 9;
                            t[8] = 9;
                            t[9] = 6;
                            t[10] = 1;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 2;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 0;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 1;
                            t[38] = 2;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 7;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 7;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 7;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 2;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 7;
                            t[7] = 9;
                            t[8] = 9;
                            t[9] = 6;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 6;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 7;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 2;
                            t[1] = 3;
                            t[2] = 6;
                            t[3] = 7;
                            t[4] = 0;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 0;
                            t[9] = 6;
                            t[10] = 8;
                            t[11] = 7;
                            t[12] = 1;
                            t[13] = 0;
                            t[14] = 8;
                            t[15] = 7;
                            t[16] = 6;
                            t[17] = 3;
                            t[18] = 8;
                            t[19] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 2;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 0;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 7;
                            t[42] = 0;
                            t[43] = 10;
                            t[44] = 0;
                            t[45] = 7;
                            t[46] = 2;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
        }
        if (edges[1] == 5) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 0;
                            t[10] = 9;
                            t[11] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 5;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 9;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 5;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 0;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 7;
                            t[30] = 0;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 7;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 5;
                            t[38] = 7;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 7;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 7;
                            t[8] = 3;
                            t[9] = 0;
                            t[10] = 9;
                            t[11] = 7;
                            t[12] = 1;
                            t[13] = 0;
                            t[14] = 3;
                            t[15] = 7;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 1;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 5;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 5;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 3;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 7;
                            t[30] = 0;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 7;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 5;
                            t[38] = 7;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 3;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 3;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 6;
                            t[10] = 2;
                            t[11] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 5;
                            t[5] = 6;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 9;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 9;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 3;
                            t[1] = 7;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 3;
                            t[5] = 2;
                            t[6] = 7;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 6;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 6;
                            t[16] = 2;
                            t[17] = 5;
                            t[18] = 7;
                            t[19] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 2;
                            t[1] = 3;
                            t[2] = 5;
                            t[3] = 7;
                            t[4] = 5;
                            t[5] = 3;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 7;
                            t[12] = 0;
                            t[13] = 6;
                            t[14] = 1;
                            t[15] = 7;
                            t[16] = 6;
                            t[17] = 3;
                            t[18] = 1;
                            t[19] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 1;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 0;
                            t[39] = 10;
                            t[40] = 0;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 6;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 6;
                            t[16] = 2;
                            t[17] = 5;
                            t[18] = 7;
                            t[19] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 5;
                            t[1] = 0;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 5;
                            t[5] = 6;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 7;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 7;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 9;
                            t[15] = 7;
                            t[16] = 1;
                            t[17] = 0;
                            t[18] = 6;
                            t[19] = 7;
                            t[20] = 1;
                            t[21] = 6;
                            t[22] = 3;
                            t[23] = 7;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 5;
                            t[2] = 6;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 0;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 9;
                            t[27] = 3;
                        }
                    }
                }
            }
        }
    }
    if (edges[0] == 1) {
        if (edges[1] == 0) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 3;
                            t[5] = 8;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 0;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 3;
                            t[9] = 8;
                            t[10] = 0;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 0;
                            t[15] = 9;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 6;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 1;
                            t[3] = 2;
                            t[4] = 1;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 3;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 0;
                            t[38] = 1;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 0;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 6;
                            t[10] = 9;
                            t[11] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 1;
                            t[3] = 2;
                            t[4] = 1;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 3;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 1;
                            t[3] = 2;
                            t[4] = 1;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 3;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 2;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 2;
                            t[38] = 0;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 6;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 6;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 6;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 6;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 3;
                            t[9] = 2;
                            t[10] = 8;
                            t[11] = 6;
                            t[12] = 1;
                            t[13] = 7;
                            t[14] = 0;
                            t[15] = 6;
                            t[16] = 2;
                            t[17] = 0;
                            t[18] = 7;
                            t[19] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 6;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 6;
                            t[12] = 1;
                            t[13] = 7;
                            t[14] = 0;
                            t[15] = 6;
                            t[16] = 2;
                            t[17] = 0;
                            t[18] = 7;
                            t[19] = 6;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 9;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 6;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 7;
                            t[42] = 0;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 0;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
        }
        if (edges[1] == 2) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 0;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 0;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 7;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 7;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 0;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 7;
                            t[5] = 2;
                            t[6] = 0;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 0;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 0;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 0;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 1;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 0;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 0;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 0;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 0;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 1;
                            t[9] = 9;
                            t[10] = 6;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 6;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 6;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 6;
                            t[12] = 0;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 6;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 1;
                            t[9] = 9;
                            t[10] = 6;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 6;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 7;
                            t[13] = 2;
                            t[14] = 6;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 7;
                            t[13] = 2;
                            t[14] = 6;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 7;
                            t[13] = 2;
                            t[14] = 6;
                            t[15] = 9;
                            t[16] = 7;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 8;
                            t[12] = 7;
                            t[13] = 2;
                            t[14] = 6;
                            t[15] = 8;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 6;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 6;
                            t[12] = 0;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 6;
                            t[16] = 0;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 6;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 6;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 6;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 6;
                            t[16] = 0;
                            t[17] = 1;
                            t[18] = 7;
                            t[19] = 6;
                            t[20] = 0;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 6;
                        }
                    }
                }
            }
        }
        if (edges[1] == 5) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 0;
                            t[10] = 9;
                            t[11] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 8;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 2;
                            t[2] = 5;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 0;
                            t[10] = 9;
                            t[11] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 5;
                            t[3] = 9;
                            t[4] = 5;
                            t[5] = 7;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 0;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 1;
                            t[25] = 0;
                            t[26] = 3;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 1;
                            t[30] = 5;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 7;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 5;
                            t[38] = 7;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 1;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 9;
                            t[11] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 3;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 7;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 8;
                            t[4] = 0;
                            t[5] = 8;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 3;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 5;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 6;
                            t[10] = 2;
                            t[11] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 9;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 2;
                            t[2] = 6;
                            t[3] = 1;
                            t[4] = 0;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 6;
                            t[10] = 2;
                            t[11] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 9;
                            t[2] = 5;
                            t[3] = 1;
                            t[4] = 5;
                            t[5] = 9;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 9;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 7;
                            t[8] = 6;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 0;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 6;
                            t[12] = 1;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 6;
                            t[16] = 2;
                            t[17] = 5;
                            t[18] = 7;
                            t[19] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 6;
                            t[34] = 3;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 1;
                            t[38] = 5;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 1;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 1;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 9;
                            t[27] = 3;
                        }
                    }
                }
            }
        }
    }
    if (edges[0] == 4) {
        if (edges[1] == 0) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 8;
                            t[5] = 4;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 8;
                            t[1] = 1;
                            t[2] = 4;
                            t[3] = 9;
                            t[4] = 8;
                            t[5] = 4;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 0;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 2;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 4;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 4;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 4;
                            t[14] = 9;
                            t[15] = 3;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 4;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 1;
                            t[14] = 4;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 3;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 3;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 4;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 4;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 4;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 4;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 4;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 1;
                            t[14] = 4;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 3;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 3;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 3;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 3;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 2;
                            t[3] = 4;
                            t[4] = 2;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 4;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 4;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 4;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 3;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 7;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 7;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 1;
                            t[14] = 4;
                            t[15] = 9;
                            t[16] = 3;
                            t[17] = 4;
                            t[18] = 0;
                            t[19] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 2;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 0;
                            t[13] = 2;
                            t[14] = 3;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 3;
                            t[18] = 4;
                            t[19] = 10;
                            t[20] = 4;
                            t[21] = 3;
                            t[22] = 8;
                            t[23] = 10;
                            t[24] = 1;
                            t[25] = 4;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 7;
                            t[30] = 4;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 7;
                            t[34] = 0;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 0;
                            t[38] = 7;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 2;
                            t[1] = 3;
                            t[2] = 0;
                            t[3] = 7;
                            t[4] = 0;
                            t[5] = 3;
                            t[6] = 4;
                            t[7] = 7;
                            t[8] = 4;
                            t[9] = 3;
                            t[10] = 8;
                            t[11] = 7;
                            t[12] = 1;
                            t[13] = 4;
                            t[14] = 8;
                            t[15] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 9;
                            t[22] = 3;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 3;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 4;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 0;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 0;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 0;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 4;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 4;
                            t[14] = 0;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 6;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 3;
                            t[5] = 4;
                            t[6] = 6;
                            t[7] = 2;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 4;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 3;
                            t[1] = 4;
                            t[2] = 6;
                            t[3] = 9;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 4;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 4;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 2;
                            t[19] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 3;
                            t[14] = 8;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 3;
                            t[14] = 8;
                            t[15] = 2;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 4;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 2;
                            t[41] = 0;
                            t[42] = 4;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 4;
                            t[46] = 1;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 6;
                            t[1] = 4;
                            t[2] = 0;
                            t[3] = 2;
                            t[4] = 6;
                            t[5] = 1;
                            t[6] = 4;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 6;
                            t[6] = 1;
                            t[7] = 2;
                            t[8] = 6;
                            t[9] = 3;
                            t[10] = 1;
                            t[11] = 2;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 9;
                            t[8] = 6;
                            t[9] = 4;
                            t[10] = 0;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 4;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 6;
                            t[8] = 6;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 3;
                            t[14] = 8;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 6;
                            t[2] = 4;
                            t[3] = 2;
                            t[4] = 4;
                            t[5] = 6;
                            t[6] = 8;
                            t[7] = 2;
                            t[8] = 1;
                            t[9] = 4;
                            t[10] = 8;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 3;
                            t[14] = 8;
                            t[15] = 2;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 2;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 4;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 2;
                            t[42] = 4;
                            t[43] = 10;
                            t[44] = 4;
                            t[45] = 2;
                            t[46] = 0;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 6;
                            t[1] = 1;
                            t[2] = 4;
                            t[3] = 7;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 0;
                            t[7] = 7;
                            t[8] = 6;
                            t[9] = 7;
                            t[10] = 0;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 4;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 6;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 1;
                            t[1] = 7;
                            t[2] = 4;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 0;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 4;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 4;
                            t[18] = 0;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 1;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 6;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 0;
                            t[19] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 0;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 6;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 6;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 6;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 0;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 2;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 2;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 0;
                            t[13] = 2;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 3;
                            t[17] = 6;
                            t[18] = 2;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 6;
                            t[22] = 4;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 6;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 4;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 0;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 0;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 2;
                            t[1] = 3;
                            t[2] = 6;
                            t[3] = 7;
                            t[4] = 2;
                            t[5] = 6;
                            t[6] = 0;
                            t[7] = 7;
                            t[8] = 0;
                            t[9] = 6;
                            t[10] = 4;
                            t[11] = 7;
                            t[12] = 4;
                            t[13] = 6;
                            t[14] = 8;
                            t[15] = 7;
                            t[16] = 1;
                            t[17] = 4;
                            t[18] = 8;
                            t[19] = 7;
                            t[20] = 6;
                            t[21] = 3;
                            t[22] = 8;
                            t[23] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 14;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 9;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 4;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 6;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 4;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 6;
                            t[41] = 3;
                            t[42] = 8;
                            t[43] = 10;
                            t[44] = 1;
                            t[45] = 7;
                            t[46] = 4;
                            t[47] = 10;
                            t[48] = 4;
                            t[49] = 7;
                            t[50] = 0;
                            t[51] = 10;
                            t[52] = 2;
                            t[53] = 0;
                            t[54] = 7;
                            t[55] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
        }
        if (edges[1] == 2) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 9;
                            t[12] = 9;
                            t[13] = 4;
                            t[14] = 1;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 3;
                            t[17] = 0;
                            t[18] = 9;
                            t[19] = 10;
                            t[20] = 4;
                            t[21] = 0;
                            t[22] = 8;
                            t[23] = 10;
                            t[24] = 1;
                            t[25] = 4;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 3;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 2;
                            t[35] = 10;
                            t[36] = 4;
                            t[37] = 1;
                            t[38] = 2;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 0;
                            t[9] = 8;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 7;
                            t[7] = 9;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 4;
                            t[14] = 9;
                            t[15] = 3;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 9;
                            t[4] = 4;
                            t[5] = 9;
                            t[6] = 0;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 9;
                            t[12] = 9;
                            t[13] = 4;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 7;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 2;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 3;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 4;
                            t[17] = 0;
                            t[18] = 8;
                            t[19] = 10;
                            t[20] = 1;
                            t[21] = 4;
                            t[22] = 8;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 4;
                            t[30] = 2;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 7;
                            t[34] = 4;
                            t[35] = 10;
                            t[36] = 4;
                            t[37] = 7;
                            t[38] = 2;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 0;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 0;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 4;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 4;
                            t[38] = 2;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 7;
                            t[42] = 4;
                            t[43] = 10;
                            t[44] = 4;
                            t[45] = 7;
                            t[46] = 2;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 9;
                            t[11] = 1;
                            t[12] = 4;
                            t[13] = 9;
                            t[14] = 3;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 9;
                            t[12] = 9;
                            t[13] = 4;
                            t[14] = 1;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 4;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 4;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 4;
                            t[12] = 0;
                            t[13] = 2;
                            t[14] = 9;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 4;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 9;
                            t[11] = 1;
                            t[12] = 4;
                            t[13] = 9;
                            t[14] = 3;
                            t[15] = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 2;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 2;
                            t[7] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 9;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 9;
                            t[14] = 3;
                            t[15] = 8;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 2;
                            t[19] = 8;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 7;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 3;
                            t[7] = 1;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 3;
                            t[11] = 7;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 9;
                            t[11] = 7;
                            t[12] = 4;
                            t[13] = 7;
                            t[14] = 9;
                            t[15] = 1;
                            t[16] = 4;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 2;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 9;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 9;
                            t[12] = 9;
                            t[13] = 4;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 7;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 4;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 4;
                            t[12] = 0;
                            t[13] = 2;
                            t[14] = 3;
                            t[15] = 4;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 4;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 4;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 2;
                            t[18] = 9;
                            t[19] = 4;
                            t[20] = 0;
                            t[21] = 9;
                            t[22] = 3;
                            t[23] = 4;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 4;
                            t[9] = 9;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 4;
                            t[14] = 1;
                            t[15] = 9;
                            t[16] = 9;
                            t[17] = 4;
                            t[18] = 1;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 8;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 2;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 6;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 4;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 0;
                            t[41] = 4;
                            t[42] = 2;
                            t[43] = 10;
                            t[44] = 4;
                            t[45] = 1;
                            t[46] = 2;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 9;
                            t[15] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 4;
                            t[9] = 9;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 6;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 7;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 6;
                            t[11] = 7;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 7;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 6;
                            t[11] = 1;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 1;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 9;
                            t[8] = 4;
                            t[9] = 9;
                            t[10] = 6;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 4;
                            t[14] = 7;
                            t[15] = 9;
                            t[16] = 9;
                            t[17] = 4;
                            t[18] = 7;
                            t[19] = 3;
                            t[20] = 4;
                            t[21] = 1;
                            t[22] = 7;
                            t[23] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 2;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 2;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 3;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 3;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 3;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 2;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 6;
                            t[22] = 4;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 6;
                            t[26] = 8;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 4;
                            t[30] = 8;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 4;
                            t[38] = 2;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 7;
                            t[42] = 4;
                            t[43] = 10;
                            t[44] = 4;
                            t[45] = 7;
                            t[46] = 2;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 14;
                            t[0] = 1;
                            t[1] = 8;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 8;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 9;
                            t[14] = 8;
                            t[15] = 10;
                            t[16] = 2;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 2;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 4;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 6;
                            t[34] = 8;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 4;
                            t[38] = 8;
                            t[39] = 10;
                            t[40] = 6;
                            t[41] = 3;
                            t[42] = 8;
                            t[43] = 10;
                            t[44] = 0;
                            t[45] = 4;
                            t[46] = 2;
                            t[47] = 10;
                            t[48] = 1;
                            t[49] = 7;
                            t[50] = 4;
                            t[51] = 10;
                            t[52] = 4;
                            t[53] = 7;
                            t[54] = 2;
                            t[55] = 10;
                            (*nint) = 1;
                        }
                    }
                }
            }
        }
        if (edges[1] == 5) {
            if (edges[2] == 0) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 1;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 3;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 5;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 5;
                            t[1] = 1;
                            t[2] = 2;
                            t[3] = 9;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 5;
                            t[7] = 9;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 0;
                            t[13] = 4;
                            t[14] = 9;
                            t[15] = 3;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 10;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 10;
                            t[16] = 3;
                            t[17] = 0;
                            t[18] = 9;
                            t[19] = 10;
                            t[20] = 4;
                            t[21] = 0;
                            t[22] = 3;
                            t[23] = 10;
                            t[24] = 1;
                            t[25] = 4;
                            t[26] = 3;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 4;
                            t[30] = 5;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 1;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 5;
                            t[38] = 1;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 8;
                            t[14] = 2;
                            t[15] = 3;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 8;
                            t[8] = 8;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 2;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 4;
                            t[4] = 3;
                            t[5] = 9;
                            t[6] = 1;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 4;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 4;
                            t[16] = 3;
                            t[17] = 0;
                            t[18] = 9;
                            t[19] = 4;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 1;
                            t[1] = 9;
                            t[2] = 2;
                            t[3] = 4;
                            t[4] = 1;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 4;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 0;
                            t[15] = 4;
                            t[16] = 3;
                            t[17] = 0;
                            t[18] = 9;
                            t[19] = 4;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 0;
                            t[13] = 8;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 9;
                            t[23] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 5;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 5;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 0;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 3;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 0;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 0;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 0;
                            t[26] = 3;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 4;
                            t[30] = 3;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 0;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 3;
                            t[20] = 5;
                            t[21] = 8;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 4;
                            t[1] = 5;
                            t[2] = 0;
                            t[3] = 8;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 8;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 0;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                            t[24] = 0;
                            t[25] = 8;
                            t[26] = 9;
                            t[27] = 3;
                        }
                    }
                }
            }
            if (edges[2] == 3) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 1;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 1;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 1;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 3;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 1;
                            t[7] = 3;
                            t[8] = 3;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 9;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 1;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 3;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 2;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 2;
                            t[10] = 5;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 2;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 4;
                            t[4] = 3;
                            t[5] = 9;
                            t[6] = 1;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 4;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 3;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 5;
                            t[18] = 3;
                            t[19] = 4;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 3;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 2;
                            t[7] = 9;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 9;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 9;
                            t[16] = 4;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 3;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 2;
                            t[18] = 5;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 2;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 3;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 5;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 1;
                            t[5] = 7;
                            t[6] = 4;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 7;
                            t[10] = 5;
                            t[11] = 3;
                            t[12] = 2;
                            t[13] = 5;
                            t[14] = 7;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 3;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 3;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 3;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 3;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 7;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 5;
                            t[5] = 4;
                            t[6] = 7;
                            t[7] = 3;
                            t[8] = 4;
                            t[9] = 1;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 3;
                            t[13] = 7;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 9;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 3;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 2;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 3;
                            t[20] = 5;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 3;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 3;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 5;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 9;
                            t[24] = 3;
                            t[25] = 8;
                            t[26] = 5;
                            t[27] = 9;
                        }
                    }
                }
            }
            if (edges[2] == 6) {
                if (edges[3] == 1) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 6;
                            t[9] = 1;
                            t[10] = 5;
                            t[11] = 2;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 3;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 1;
                            t[8] = 5;
                            t[9] = 1;
                            t[10] = 2;
                            t[11] = 9;
                            t[12] = 6;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 6;
                            t[17] = 1;
                            t[18] = 9;
                            t[19] = 3;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 10;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 2;
                            t[3] = 10;
                            t[4] = 5;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 10;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 10;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 2;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 6;
                            t[18] = 4;
                            t[19] = 10;
                            t[20] = 4;
                            t[21] = 6;
                            t[22] = 3;
                            t[23] = 10;
                            t[24] = 1;
                            t[25] = 4;
                            t[26] = 3;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 4;
                            t[30] = 5;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 1;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 2;
                            t[37] = 5;
                            t[38] = 1;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 3;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 1;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 10;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 5;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 6;
                            t[30] = 3;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 4;
                            t[34] = 3;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 4;
                            t[38] = 5;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 1;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 1;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 2;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 5;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 5;
                            t[17] = 8;
                            t[18] = 2;
                            t[19] = 3;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 1;
                            t[11] = 8;
                            t[12] = 8;
                            t[13] = 1;
                            t[14] = 5;
                            t[15] = 9;
                            t[16] = 5;
                            t[17] = 1;
                            t[18] = 2;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 9;
                            t[27] = 3;
                        }
                    }
                }
                if (edges[3] == 2) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 3;
                            t[1] = 2;
                            t[2] = 1;
                            t[3] = 6;
                            t[4] = 0;
                            t[5] = 4;
                            t[6] = 5;
                            t[7] = 6;
                            t[8] = 1;
                            t[9] = 2;
                            t[10] = 4;
                            t[11] = 6;
                            t[12] = 4;
                            t[13] = 2;
                            t[14] = 5;
                            t[15] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 10;
                            t[0] = 2;
                            t[1] = 1;
                            t[2] = 3;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 3;
                            t[6] = 5;
                            t[7] = 10;
                            t[8] = 5;
                            t[9] = 3;
                            t[10] = 6;
                            t[11] = 10;
                            t[12] = 0;
                            t[13] = 5;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 6;
                            t[18] = 4;
                            t[19] = 10;
                            t[20] = 4;
                            t[21] = 6;
                            t[22] = 1;
                            t[23] = 10;
                            t[24] = 6;
                            t[25] = 3;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 4;
                            t[30] = 5;
                            t[31] = 10;
                            t[32] = 1;
                            t[33] = 2;
                            t[34] = 4;
                            t[35] = 10;
                            t[36] = 4;
                            t[37] = 2;
                            t[38] = 5;
                            t[39] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 12;
                            t[0] = 2;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 3;
                            t[5] = 9;
                            t[6] = 1;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 10;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 5;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 10;
                            t[24] = 0;
                            t[25] = 6;
                            t[26] = 4;
                            t[27] = 10;
                            t[28] = 4;
                            t[29] = 6;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 6;
                            t[33] = 3;
                            t[34] = 1;
                            t[35] = 10;
                            t[36] = 0;
                            t[37] = 4;
                            t[38] = 5;
                            t[39] = 10;
                            t[40] = 1;
                            t[41] = 2;
                            t[42] = 4;
                            t[43] = 10;
                            t[44] = 4;
                            t[45] = 2;
                            t[46] = 5;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 4;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 2;
                            t[3] = 4;
                            t[4] = 5;
                            t[5] = 2;
                            t[6] = 6;
                            t[7] = 4;
                            t[8] = 0;
                            t[9] = 5;
                            t[10] = 6;
                            t[11] = 4;
                            t[12] = 3;
                            t[13] = 6;
                            t[14] = 2;
                            t[15] = 4;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 4;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 6;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 9;
                            t[3] = 4;
                            t[4] = 1;
                            t[5] = 9;
                            t[6] = 2;
                            t[7] = 4;
                            t[8] = 2;
                            t[9] = 9;
                            t[10] = 5;
                            t[11] = 4;
                            t[12] = 5;
                            t[13] = 9;
                            t[14] = 6;
                            t[15] = 4;
                            t[16] = 0;
                            t[17] = 5;
                            t[18] = 6;
                            t[19] = 4;
                            t[20] = 3;
                            t[21] = 6;
                            t[22] = 9;
                            t[23] = 4;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 6;
                            t[17] = 8;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 2;
                            t[23] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 6;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 2;
                            t[18] = 5;
                            t[19] = 3;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 2;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 2;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 2;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 9;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 9;
                            t[27] = 3;
                        }
                    }
                }
                if (edges[3] == 7) {
                    if (edges[4] == 1) {
                        if (edges[5] == 2) {
                            (*nel) = 6;
                            t[0] = 3;
                            t[1] = 2;
                            t[2] = 7;
                            t[3] = 6;
                            t[4] = 3;
                            t[5] = 7;
                            t[6] = 1;
                            t[7] = 6;
                            t[8] = 0;
                            t[9] = 4;
                            t[10] = 5;
                            t[11] = 6;
                            t[12] = 1;
                            t[13] = 7;
                            t[14] = 4;
                            t[15] = 6;
                            t[16] = 4;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 6;
                            t[20] = 2;
                            t[21] = 5;
                            t[22] = 7;
                            t[23] = 6;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 12;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 3;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 3;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 3;
                            t[10] = 5;
                            t[11] = 10;
                            t[12] = 5;
                            t[13] = 3;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 0;
                            t[17] = 5;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 6;
                            t[22] = 4;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 6;
                            t[26] = 1;
                            t[27] = 10;
                            t[28] = 6;
                            t[29] = 3;
                            t[30] = 1;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 14;
                            t[0] = 7;
                            t[1] = 1;
                            t[2] = 9;
                            t[3] = 10;
                            t[4] = 2;
                            t[5] = 7;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 3;
                            t[9] = 9;
                            t[10] = 1;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 4;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 6;
                            t[34] = 1;
                            t[35] = 10;
                            t[36] = 6;
                            t[37] = 3;
                            t[38] = 1;
                            t[39] = 10;
                            t[40] = 0;
                            t[41] = 4;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 1;
                            t[45] = 7;
                            t[46] = 4;
                            t[47] = 10;
                            t[48] = 4;
                            t[49] = 7;
                            t[50] = 5;
                            t[51] = 10;
                            t[52] = 2;
                            t[53] = 5;
                            t[54] = 7;
                            t[55] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 3) {
                        if (edges[5] == 2) {
                            (*nel) = 12;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 2;
                            t[7] = 10;
                            t[8] = 5;
                            t[9] = 2;
                            t[10] = 6;
                            t[11] = 10;
                            t[12] = 0;
                            t[13] = 5;
                            t[14] = 6;
                            t[15] = 10;
                            t[16] = 3;
                            t[17] = 6;
                            t[18] = 2;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 6;
                            t[22] = 4;
                            t[23] = 10;
                            t[24] = 4;
                            t[25] = 6;
                            t[26] = 3;
                            t[27] = 10;
                            t[28] = 1;
                            t[29] = 4;
                            t[30] = 3;
                            t[31] = 10;
                            t[32] = 0;
                            t[33] = 4;
                            t[34] = 5;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 7;
                            t[38] = 4;
                            t[39] = 10;
                            t[40] = 4;
                            t[41] = 7;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 2;
                            t[45] = 5;
                            t[46] = 7;
                            t[47] = 10;
                            (*nint) = 1;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 5;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 3;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 3;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 3;
                            t[16] = 5;
                            t[17] = 7;
                            t[18] = 2;
                            t[19] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 14;
                            t[0] = 1;
                            t[1] = 3;
                            t[2] = 7;
                            t[3] = 10;
                            t[4] = 7;
                            t[5] = 3;
                            t[6] = 9;
                            t[7] = 10;
                            t[8] = 2;
                            t[9] = 7;
                            t[10] = 9;
                            t[11] = 10;
                            t[12] = 2;
                            t[13] = 9;
                            t[14] = 5;
                            t[15] = 10;
                            t[16] = 5;
                            t[17] = 9;
                            t[18] = 6;
                            t[19] = 10;
                            t[20] = 0;
                            t[21] = 5;
                            t[22] = 6;
                            t[23] = 10;
                            t[24] = 3;
                            t[25] = 6;
                            t[26] = 9;
                            t[27] = 10;
                            t[28] = 0;
                            t[29] = 6;
                            t[30] = 4;
                            t[31] = 10;
                            t[32] = 4;
                            t[33] = 6;
                            t[34] = 3;
                            t[35] = 10;
                            t[36] = 1;
                            t[37] = 4;
                            t[38] = 3;
                            t[39] = 10;
                            t[40] = 0;
                            t[41] = 4;
                            t[42] = 5;
                            t[43] = 10;
                            t[44] = 1;
                            t[45] = 7;
                            t[46] = 4;
                            t[47] = 10;
                            t[48] = 4;
                            t[49] = 7;
                            t[50] = 5;
                            t[51] = 10;
                            t[52] = 2;
                            t[53] = 5;
                            t[54] = 7;
                            t[55] = 10;
                            (*nint) = 1;
                        }
                    }
                    if (edges[4] == 8) {
                        if (edges[5] == 2) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 2;
                            t[20] = 6;
                            t[21] = 8;
                            t[22] = 5;
                            t[23] = 2;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 2;
                            t[27] = 3;
                        }
                        if (edges[5] == 3) {
                            (*nel) = 7;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 3;
                            t[20] = 5;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 3;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 5;
                            t[27] = 3;
                        }
                        if (edges[5] == 9) {
                            (*nel) = 8;
                            t[0] = 0;
                            t[1] = 4;
                            t[2] = 5;
                            t[3] = 6;
                            t[4] = 4;
                            t[5] = 5;
                            t[6] = 6;
                            t[7] = 8;
                            t[8] = 5;
                            t[9] = 4;
                            t[10] = 7;
                            t[11] = 8;
                            t[12] = 4;
                            t[13] = 1;
                            t[14] = 7;
                            t[15] = 8;
                            t[16] = 8;
                            t[17] = 7;
                            t[18] = 5;
                            t[19] = 9;
                            t[20] = 5;
                            t[21] = 7;
                            t[22] = 2;
                            t[23] = 9;
                            t[24] = 6;
                            t[25] = 8;
                            t[26] = 5;
                            t[27] = 9;
                            t[28] = 6;
                            t[29] = 8;
                            t[30] = 9;
                            t[31] = 3;
                        }
                    }
                }
            }
        }
    }
    return true;
}

