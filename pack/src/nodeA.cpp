   #include "ros/ros.h"
   #include <stdio.h>      /* printf, scanf, puts, NULL */
   #include <stdlib.h>     /* srand, rand */
   #include <time.h>       /* time */
   #include "std_msgs/String.h"
   #include "std_msgs/Bool.h"
   #include "std_msgs/Int16.h"
   #include "std_msgs/Float32.h"
   #include <sstream>
   
 
    
   int main(int argc, char**argv)
   {
     
     ros::init(argc, argv, "nodeA");
   
 
     ros::NodeHandle a;
   
    /* con la función node.advertise() se obtiene un objeto tipo publisher que permitirá publicar topics. con advertise de <std_msgs::String> 		se especifica que se publicarpa un topic de variable String. el primer parámetro especifica el nombre del topic y el segundo el tamaño 		del buffer o "cola" que funciona como bandeja en caso que los mensajes son publicados más rapido de lo que se pueden enviar*/

     //ros::Publisher chatter_pub = a.advertise<std_msgs::String>("chatter", 1000);
   /*Rate permite especificar la frecuencia con que se desea publicar el topic (en este caso 10Hz)*/

     ros::Publisher paraB = a.advertise<std_msgs::Bool>("chatB", 1000);
     ros::Publisher paraC = a.advertise<std_msgs::Int16>("chatC", 1000);
     ros::Publisher paraD = a.advertise<std_msgs::Float32>("chatD", 1000);

     ros::Rate loop_rate(10);
   /*crea una variable que llevará la cuenta de cuantos mensajes se han enviado y se inicia el ciclo que mantendrá activo el nodo*/
     
     srand(time(NULL));
     int count = 0;
     while (ros::ok())
     {
       /*se crea una variable del mismo tipo que se especificó en el topic que se publicará, además se imprime para visualizar el mensaje en el 	terminal con ROS_INFO*/
       
         
       std_msgs::Bool bol;
       std_msgs::Int16 ent;
       std_msgs::Float32 flot;

       bol.data=rand()% 2;
       ent.data=600;/*rand()% 1025;*/
       flot.data=30.5;//float(rand()% 201+(rand()%1000)/1000.0);
   
       /*std::stringstream ss;
       ss << "hello world " << count;
       msg.data = ss.str();*/
       
       ROS_INFO("%d \n", ent.data);
       ROS_INFO("%f \n", flot.data); 
   
       //ROS_INFO("%s", msg.data.c_str());
   
      /*La función publish() es la que se utiliza para publicar el mensaje y el parámetro es el objeto creado que almacena el contenido a 		enviar y debe ser el mismo especificado en la funcion advertise()*/

      paraB.publish(bol);
      paraC.publish(ent);
      paraD.publish(flot);
  
	/*la siguiente función permite que lleguen las callbacks de los nodos que se suscriban al topic que está publicando*/
      
	ros::spinOnce();

  	/*con rate.sleep() se complementa la frecuencia para evitar que se publiquen topics a una frecuencia diferente a la especificada anterionrmente*/

      loop_rate.sleep();
      ++count;
    }
  
  
    return 0;
   }
