
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int mesh[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
int gN = 16;
int gNodes=16;
int gK=4;
int k=4;
int bi ;
int count=1;
int dor_next_mesh( int cur, int dest, int descending );
int array_fault[1] = {8};
/*void insert_random_fault(){
  int found , temp;
  count = rand()%(k*k);
  int index=0;
  for(int i=0; i< count ; i++){
      array_fault[i]=-1;
  }
  /*for(int i=0; i< count ; i++){
      //check doesnt produce same random number
      /*while(found == 0){
         temp = rand()%(k*k);
         int found=0;
         for(int j=0;j<index;j++){
             if(array_fault[j] == temp)
                 found=1;
         }
      }*/
      //array of faulty node
/*
      temp = rand()%(k*k);
      array_fault[index] = temp;
      index++;
  }*//*
  array_fault[0] = 9;


  printf("faulty node = \t");
  for(int i=0;i<count;i++){
      printf("  %d" , array_fault[i]);
    }
    printf("\n");
}*/
int check(int node){
    //creat random array of faulty node
    int  out;
    out = 1;
    for(int i=0;i<count;i++){
        if(node == array_fault[i]){
            out = 0; //there is inn faulty node
        }
    }
    if(node >= (k*k) || node <0) out=0;

    return out;
}

int west_or_east(int node , int dest){// return 0 if east and 1 if west
    //printf("west_or_east\n");
    int out;
    int i_node = node / k;
    int j_node = node % k;
    if(node/k < dest/k){//go down
        int out_east = (i_node)*k + (j_node+1);
        int out_southeast = (i_node + 1)*k + (j_node+1);
        int out_west = (i_node)*k + (j_node-1);
        int out_southwest = (i_node + 1)*k + (j_node-1);

        if (check(out_east) && check(out_southeast)){
            if (check(out_west) && check(out_southwest)){
                int random = 0;//rand()%2;
                if(random == 1){
                   //printf("east\n");
                    out=1; //east
                }
                else{
                  //printf("west\n");
                  out = 0;//west
                }

            }
            else{
                //printf("east\n");
                out=1; //east
            }
        }
        else{
            if (check(out_west) && check(out_southwest)){
                //printf("west\n");
                out = 0;//west
            }
            else{
              if(node%k+2 < dest%k){//east
                if (check(out_east) && check((node/k)*k+(node%k +2))){
                  out = 0;//east
                }
              }
              else if(node%k-2 > dest%k){//west
                if (check(out_west) && check((node/k)*k+(node%k -2))){
                  out = 1;//west
                }
              }
                out = -1;//network broke;
            }
        }
    }
    else{//go up
        int out_east = (i_node)*k + (j_node+1);
        int out_northeast = (i_node - 1)*k + (j_node+1);
        int out_west = (i_node)*k + (j_node-1);
        int out_northwest = (i_node - 1)*k + (j_node-1);

        if (check(out_east) && check(out_northeast)){
            if (check(out_west) && check(out_northwest)){
                int random = 1;//rand()%2;
                if(random == 1){
                    //printf("east\n");
                    out=1; //east
                }
                else{
                  //printf("west\n");
                  out = 0;//west
                }

            }
            else{
              if(node%k+2 < dest%k){//east
                if (check(out_east) && check((node/k)*k+(node%k +2))){
                  out = 0;//east
                }
              }
              else if(node%k-2 > dest%k){//west
                if (check(out_west) && check((node/k)*k+(node%k -2))){
                  out = 1;//west
                }
              }
                out=1; //east
            }
        }
        else{
            if (check(out_west) && check(out_northwest)){
                out = 0;//west
                //printf("west\n");
            }
            else{
                out = -1;//network broke;
            }
        }
    }
    return out;
}

int north_or_south(int node , int dest){// return 0 if north and 1 if south
    //printf("north_or_south\n");
    int out;
    int i_node = node / k;
    int j_node = node % k;
    if(node%k < dest%k){//go east

        int out_south = (i_node+1)*k + (j_node);
        int out_southeast = (i_node + 1)*k + (j_node+1);
        int out_north = (i_node-1)*k + (j_node);
        int out_northeast = (i_node - 1)*k + (j_node+1);

        if (check(out_south) && check(out_southeast)){
            if (check(out_north) && check(out_northeast)){
                if( node/k < dest/k){
                   out = 1;//south
                   //printf("south\n");
                }
                else{

                   //printf("north\n");
                   out=0; //north
                }
            }
            else{
                //printf("south\n");
                out=1; //south

            }
        }
        else{
            if (check(out_north) && check(out_northeast)){
                //printf("north\n");
                out = 0;//north
            }
            else{
              if(node/k+2 < dest/k){//south
                if (check(out_south) && check((node/k +2)*k+(node%k))){
                  out = 1;//south
                }
              }
              else if(node/k-2 > dest/k){
                if (check(out_north) && check((node/k -2)*k+(node%k))){
                  out = 0;//north
                }
              }
              else
                out = -1;//network broke;
            }
        }

    }
    else{//go west

        int out_south = (i_node+1)*k + (j_node);
        int out_southwest = (i_node + 1)*k + (j_node-1);
        int out_north = (i_node -1 )*k + (j_node);
        int out_northwest = (i_node - 1)*k + (j_node-1);

        if (check(out_south) && check(out_southwest)){
            if (check(out_north) && check(out_northwest)){
                if( node/k < dest/k){
                   out = 1;//south
                   //printf("south\n");
                }
                else{
                   out=0; //north
                   //printf("north\n");
                }
        }
        else{
            if (check(out_north) && check(out_northwest)){
                out = 0;//north
                //printf("north\n");
            }
            else{
                out = -1;//network broke;
            }
        }
    }
    else{
      if (check(out_north) && check(out_northwest)){
          if( node/k < dest/k){
             out = 1;//south
             //printf("south\n");
          }
          else{
             out=0; //north
             //printf("north\n");
          }
        }
        else{
          if(node/k+2 < dest/k){//south
            if (check(out_south) && check((node/k +2)*k+(node%k))){
              out = 1;//south
            }
          }
          else if(node/k-2 > dest/k){
            if (check(out_north) && check((node/k -2)*k+(node%k))){
              out = 0;//north
            }
          }
          else{
              out = -1;//network broke;
          }
        }
    }
}
return out;
}
int xy_yx_mesh( int source, int dest ){
    //printf("%d  %d\t" , source,dest);
    int x_then_y = 1;
    int out_port;
    int output;
    if(x_then_y) {
      out_port = dor_next_mesh( source, dest, 0 );
      //printf("out_port = %d\t" , out_port);
       //
        int i_source = source / k;
        int j_source =source % k ;
        int i_dest = dest / k;
        int j_dest = dest % k ;

        if(out_port == 3){//UP
            output = (source /k - 1)*k+ (source%k);
            int j_out = source%k;
            int i_out = source/k -1;
            int out = i_out * k + j_out;
            if(!check(out)){ //if out faulty
                //printf("first is faulty\n");
                //we must go to east or west
                // we must check E,NE for east and check W , NW for west
                int a = i_source*k + j_source;
                int b = i_dest * k + j_dest;
                int condition=0;
                ////////////
                if(source%k < dest%k){//east
                  if(check((source/k-1)*k + (source%k)) && check((source/k -1)*k + (source%k +1)) ){
                    condition=1;
                    out_port=3;
                    output = (source/k-1)*k + (source%k);
                    //printf("out_port = %d\t" , out_port);
                  }
                }
                if(source%k > dest%k){//west
                  if(check((source/k-1)*k + (source%k)) && check((source/k -1)*k + (source%k -1)) ){
                    condition=1;
                    out_port=3;
                    output = (source/k-1)*k + (source%k);
                    //printf("out_port = %d\t" , out_port);
                  }
                }
                /////////
                if(condition == 0 ){
                int output_up = west_or_east(a , b);

                if(output_up == 0) {
                  out_port=0;
                  //printf("out_port = %d\t" , out_port);
                  output = source + 1;
                }
                else{
                  out_port=1;
                  //printf("out_port = %d\t" , out_port);
                  output = source - 1;
                }
              }
            }
            else{//if out doesnt faulty
                //do we arrive?
                //printf("first is non faulty\n");
                if(i_out == i_dest && j_out == j_dest){
                  //printf("we arrive\n");
                    //we arrive
                }
                else{//we keep going to up check north north
                    int out_out = (i_source -2) * k + (j_source);
                    if(check(out_out)){//non faulty
                      //printf("we keep going to up\n");
                        //its ok
                    }
                    else{//faulty we should go to west or east
                        int a = i_source*k + j_source;
                        int b = i_dest * k + j_dest;
                        int output_up1 = west_or_east(a , b);
                        if(output_up1 == 0) {
                          out_port=0;
                          //printf("out_port = %d\t" , out_port);
                          output = source + 1;
                        }
                        else{
                          out_port=1;
                          //printf("out_port = %d\t" , out_port);
                          output = source - 1;
                        }
                    }
                }
            }
        }
        if(out_port == 2){ //down
            output = (source /k +1)*k+ (source%k);
            int j_out = j_source;
            int i_out = i_source +1;
            int i_dest = dest / k;
            int j_dest = dest % k ;
            int output;
            int out = i_out * k + j_out;
            if(!check(out)){ //if out faulty
                //we must go to east or west
                // we must check E,SE for east and check W , SW for west
                int a = i_source*k + j_source;
                int b = i_dest * k + j_dest;
                int output_down=west_or_east(a , b);
                if(output_down == 0) {

                  out_port=0;
                  //printf("out_port = %d\t" , out_port);
                  output = source + 1;
                }
                else{
                  out_port=1;
                  //printf("out_port = %d\t" , out_port);
                  output = source - 1;
                }
            }
            else{//if out doesnt faulty
                 //do we arrive?
                if(i_out == i_dest && j_out == j_dest){
                //we arrive
                }
                else{//we keep going to downn check south south
                    int out_out = (i_source + 2) * k + (j_source);
                    if(check(out_out)){//non faulty
                    //its ok
                    }
                    else{//faulty we should go to west or east
                        int a = i_source*k + j_source;
                        int b = i_dest * k + j_dest;
                        int condition=0;
                        ////////////
                        if(source%k < dest%k){//east
                          if(check((source/k+1)*k + (source%k)) && check((source/k +1)*k + (source%k +1)) ){
                            condition=1;
                            out_port=2;
                            output = (source/k+1)*k + (source%k);
                            //printf("out_port = %d\t" , out_port);
                          }
                        }
                        if(source%k > dest%k){//west
                          if(check((source/k+1)*k + (source%k)) && check((source/k +1)*k + (source%k -1)) ){
                            condition=1;
                            out_port=1;
                            output = (source/k+1)*k + (source%k);
                            //printf("out_port = %d\t" , out_port);
                          }
                        }
                        /////////
                        if(condition == 0){
                        int output_down = west_or_east(a , b);
                        if(output_down == 0) {
                          out_port=0;
                          //printf("out_port = %d\t" , out_port);
                          output = source + 1;
                        }
                        else{
                          out_port=1;
                          //printf("out_port = %d\t" , out_port);
                          output = source - 1;
                        }
                      }
                        }
                    }
                }
        }
        if(out_port == 0){//east
            output = (source /k)*k+ (source%k + 1);
            int j_out = j_source+1;
            int i_out = i_source;
            int i_dest = dest / k;
            int j_dest = dest % k ;
            int out = i_out * k + j_out;
            if(!check(out)){ //if out faulty
              //printf("next node is faulty\t");
              //we must go to north or last
             // we must check E,NE for north and check S , SE for south
             int a = i_source*k + j_source;
             int b = i_dest * k + j_dest;
             int output_up = north_or_south(a , b);
             if(output_up == 0) {
               out_port=3;

               //printf("out_port = %d\t" , out_port);
               output = (source/k -1)*k + (source%k);
             }
             else{
               out_port=2;
               //printf("out_port = %d\t" , out_port);
               output = (source/k +1)*k + (source%k);
             }
            }
            else{
              //printf("next node is not faulty\t");
              //if out doesnt faulty
             //do we arrive?
            if(i_out == i_dest && j_out == j_dest){
              //printf("we arrive\t");
            //we arrive
            }
            else{//we keep going to downn check south south
              if(j_source+1 != j_dest){
                int out_out = (i_source ) * k + (j_source+2);
                if(check(out_out)){//non faulty
                //its ok
                }
                else{//faulty we should go to west or east
                    int a = i_source*k + j_source;
                    int b = i_dest * k + j_dest;
                    int condition=0;
                    /////////////////
                    if(source/k < dest/k){//south
                      if(check((source/k)*k + (source%k +1)) && check((source/k +1)*k + (source%k +1)) ){
                        condition=1;
                        out_port=0;
                        output = (source/k)*k + (source%k+1);
                        //printf("out_port = %d\t" , out_port);
                      }
                    }
                    if(source/k > dest/k){//nourh
                      if(check((source/k)*k + (source%k +1)) && check((source/k -1)*k + (source%k +1)) ){
                        condition=1;
                        out_port=0;
                        output = (source/k)*k + (source%k+1);
                        //printf("out_port = %d\t" , out_port);
                      }
                    }
                    ///////////////////
                    if(condition == 0){
                    int output_up=north_or_south(a , b);
                    if(output_up == 0) {
                      out_port=3;
                      //printf("out_port = %d\t" , out_port);
                      output = (source/k -1)*k + (source%k);
                    }
                    else{
                      out_port=2;
                      //printf("out_port = %d\t" , out_port);
                      output = (source/k +1)*k + (source%k);
                    }
                  }
                    }
                  }
                  else{
                    if(source/k < dest/k){
                      int down = (i_source+1 ) * k + (j_source+1);
                      if(check(down)){

                      }
                      else{
                        out_port=2;
                        //printf("up\t");
                        output = (i_source+1 ) * k + (j_source);
                      }
                    }
                    else{
                      int up = (i_source-1 ) * k + (j_source+1);
                      if(check(up)){

                      }
                      else{
                        out_port=3;
                        //printf("down\t");
                        output = (i_source-1 ) * k + (j_source);
                      }
                    }

                  }
                }
            }
        }
        if(out_port == 1){//west
            output = (source /k)*k+ (source%k-1);
            int i_source = source /k;
            int j_source = source %k;
            int j_out = source%k-1;
            int i_out = source /k;
            int i_dest = dest / k;
            int j_dest = dest % k ;
            int out = (source /k)*k+ (source%k-1);

            if(!check(out)){ //if out faulty
              //printf("next node is faulty\t");
              //we must go to north or last
             // we must check W,NW for north and check S , SW for south
             int a = (source /k)*k + j_source;
             int b = i_dest * k + j_dest;
             int output_up1=north_or_south(a , b);
             if(output_up1 == 0) {
               out_port=3;

               output = (source/k -1)*k + (source%k);
               //printf("out_port = %d\t" , out_port);
             }
             else{
               out_port=2;
               output = (source/k +1)*k + (source%k);
               //printf("out_port = %d\t" , out_port);
             }
            }
            else{//if out doesnt faulty
              //printf("next node is not faulty\t");
             //do we arrive?
            if(i_out == i_dest && j_out == j_dest){
              //printf("we arrive\t");
            //we arrive
            }
            else{//we keep going to downn check south south

                if(j_source-1 != j_dest){
                int out_out = (i_source ) * k + (j_source-2);
                if(check(out_out)){//non faulty
                //its ok
                }
                else{//faulty we should go to west or east
                   int condition=0;
                    int a = i_source*k + j_source;
                    int b = i_dest * k + j_dest;
                    ////////////
                    if(source/k < dest/k){//south
                      if(check((source/k)*k + (source%k -1)) && check((source/k +1)*k + (source%k -1)) ){
                        condition=1;
                        out_port=1;
                        output = (source/k)*k + (source%k-1);
                        //printf("out_port = %d\t" , out_port);
                      }
                    }
                    if(source/k > dest/k){//nourh
                      if(check((source/k)*k + (source%k -1)) && check((source/k -1)*k + (source%k -1)) ){
                        condition=1;
                        out_port=1;
                        output = (source/k)*k + (source%k-1);
                        //printf("out_port = %d\t" , out_port);
                      }
                    }
                    ////
                    if (condition == 0)
                    {
                    int output_up=north_or_south(a , b);
                    if(output_up == 0) {
                      out_port=3;
                      output = (source/k -1)*k + (source%k);
                      //printf("out_port = %d\t" , out_port);
                    }
                    else{
                      out_port=2;
                      output = (source/k +1)*k + (source%k);
                      //printf("out_port = %d\t" , out_port);
                    }
                  }

                    }
                  }
                  else{
                    if(source/k < dest/k){
                      int down = (i_source+1 ) * k + (j_source-1);
                      if(check(down)){

                      }
                      else{
                        out_port=2;
                        //printf("down\t");
                        output = (i_source+1 ) * k + (j_source);
                      }
                    }
                    else{
                      int up = (i_source-1 ) * k + (j_source-1);
                      if(check(up)){

                      }
                      else{
                        //printf("up\t");
                        out_port=3;
                        output = (i_source-1 ) * k + (j_source);
                      }
                    }
                  }

                }
            }
        }
    }
    return output;

}
int dor_next_mesh( int cur, int dest, int descending )
{
  if ( cur == dest ) {
    return 2*gN;  // Eject
  }

  int dim_left;

  if(descending) {
    for ( dim_left = ( gN - 1 ); dim_left > 0; --dim_left ) {
      if ( ( cur * gK / gNodes ) != ( dest * gK / gNodes ) ) { break; }
      cur = (cur * gK) % gNodes; dest = (dest * gK) % gNodes;
    }
    cur = (cur * gK) / gNodes;
    dest = (dest * gK) / gNodes;
  } else {
    for ( dim_left = 0; dim_left < ( gN - 1 ); ++dim_left ) {
      if ( ( cur % gK ) != ( dest % gK ) ) { break; }
      cur /= gK; dest /= gK;
    }
    cur %= gK;
    dest %= gK;
  }

  if ( cur < dest ) {
    return 2*dim_left;     // Right
  } else {
    return 2*dim_left + 1; // Left
  }
}
int XY(int source, int dest){
  int out_node;
  int out_port = dor_next_mesh( source, dest, 0 );

  if(out_port ==0){
    out_node = (source/k)*k + (source%k+1);
  }
  if(out_port ==1){
    out_node = (source/k)*k + (source%k-1);
  }
  if(out_port ==2){
    out_node = (source/k+1)*k + (source%k);
  }
  if(out_port ==3){
    out_node = (source/k-1)*k + (source%k);
  }

  return out_node;
}
int West_first(int source , int dest){
  int output;
  int out_port;
  if(rand()%2 == 0)
  out_port = dor_next_mesh( source, dest, 0 );
  else
  out_port = dor_next_mesh( source, dest, 1 );
  int column_src = source%k;
    int row_src = source/k;
    int column_dest= dest %k;
    int row_dest= dest /k;

  if(out_port == 1){ //west
     output = (column_src - 1) + row_src*k;
       if(!check(output)){
         printf("!!faulty node!");
         out_port=-1;
  }
}
  if(out_port == 0){//east
     output = (column_src + 1) + row_src*k;
     if(!check(output)){ //check up is non faulty
       if(row_dest < row_src){
           out_port = 3;
           output= column_src + (row_src - 1)*k;
         if(!check(output)){ //up is faulty so check down
           output= column_src + (row_src + 1)*k;
             out_port = 2;
           if(!check(output)){
             out_port = -1;
           }
         }
        }else if(row_dest > row_src){
         out_port = 2;
         output= column_src + (row_src + 1)*k;
         if(!check(output)){//if down faulty check up
           output= column_src + (row_src - 1)*k;
           out_port = 3;
           if(!check(output)){ // if up faulty crash
             out_port = -1;
           }
         }

       }else{
         if(check(column_src + (row_src - 1)*k )){
           if(check(column_src + (row_src + 1)*k )){
             //random
             int array[2]={-1,1};
             int rnd = rand()%2;
             int num =array[rnd];
             if(rnd == -1 ) out_port = 3;
             if(rnd == 1 ) out_port = 2;
             output= column_src + (row_src + num )*k;
           }
           else{
             //up
             out_port = 3;
             output= column_src + (row_src - 1)*k;
           }
         }
         else{//down
           out_port = 2;
           output= column_src + (row_src + 1)*k;
         }
       }
     }
   }

   if(out_port == 3){ //up
     output = column_src + (row_src-1)*k;
     if(!check(output)){
       if(column_src > column_dest){
         printf("faulty node");
         output=-1;

       }else if(column_src < column_dest){
         out_port = 0;
         output = (column_src + 1) + row_src*k;
         if(!check(output)){
          out_port = -1;
           printf("faulty node");
         }
       }else{
         if(check(column_src + (row_src + 1)*k )){//east
            out_port = 0;
           output = (column_src + 1) + row_src*k;
         }
         else{
           out_port = -1; //crash
         }
       }
     }
   }


   if(out_port == 2){//down
     output = column_src + (row_src+1)*k;

     if(!check(output)){
       if(column_src > column_dest){
         printf("faulty node");
         output = -1;
       }else if(column_src < column_dest){//east
         out_port = 0;
         output = (column_src + 1) + row_src*k;
         if(!check(output)){
            out_port = -1;
           output = -1; //crash
         }
       }else if(column_src > column_dest){
         out_port = 1;
         output = (column_src - 1) + row_src*k;
         if(!check(output)){
           output=-1; //crash
         }
       }
       else{
         output = (column_src - 1) + row_src*k;
         out_port = 1;
         if(!check(output)){

           out_port = -1; //crash
         }
       }
     }
   }
 printf("\n##%d\n",out_port);
 return output;
}

int main(){
  int a=1;
  int source=13;
  int dest =1;
  printf("\nfaulty node:");
  for(int i=0;i<1;i++)
  printf("%d\t",array_fault[i] );
  printf("\n");
  //insert_random_faul();
  printf("source is %d\t" , source);
  printf("dest is %d\n" , dest);

  printf("optimize algorithm\n");
  if(check(source)==0 || check(dest)==0){
    printf("sourth or dest is faulty\n");
  }
  else{
  int output , output1;
  output = source;
  printf("next node = \n");
 while(a==1){
   output1 = xy_yx_mesh( output, dest);
   output = output1;
   printf("%d\t",output);

   if(output == dest) break;
 }
 printf("\n");


printf("*********************************\n");
printf("XY algorithm\n");
output = source;
while(a==1){
  output1 = XY( output, dest);
  output = output1;
  printf("%d\t",output);
  if(!check(output)){
    printf("faulty node\n");
    break;
  }
  if(output == dest) break;
}

printf("\n*********************************\n");
printf("west first algorithm\n");

output = source;
while(a==1){
  output1 = West_first(output, dest);
  output = output1;
  if(output != -1)
  printf("%d\t",output);
  else
  break;

  if(output == dest) break;
}

}
printf("\n");
return 0;
}
