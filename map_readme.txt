
Testing:
Building: With make
Call ./all.a to print a run with the data.
Test assumes vanilla gcc compiler.

Map:    
Reference Direction: ^-N E->


     14*12*13
         *
         *
***11*10*9*15
*     *     *
*     *     *
*     *    16*17
*     *        *
*     *        *
5**6**8*******18
*  *  *
*  *  *
*  7  *     4
*     *     *
*     *     *
1*****2*****5

Testing Start and goal states:
Start 4
Goal 14
Expected Shortest Path:
4,5,2,8,10,9,12,14

Initial Starting Direction in tests: South

Breaking node and path adaptation tested against
by breaking the connection between nodes 2 and 8.
Expected Shortest path one of 4,3,2,1,5,11,10,9,12,14
or 4,3,2,1,6,11,10,9,12,14 (got 5 because of a northerly bias in code)
