   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include <sstream>
   #include "std_msgs/Int16.h"
   #include <iostream>
   #include <string>
   //SECCIÓN DE SUBSCRIBER DEL NODO

   //explicación nodo subscriber sencillo 

   /*la función se llamará cuando llegue un nuevo mensaje en el topic chatter*/

   std_msgs::Int16 entero;

   void chatterCallback(const std_msgs::Int16::ConstPtr& ent)
   {
     entero.data=ent->data;
     
     ROS_INFO("I heard: [%d]", entero.data);
   }
   
   int main(int argc, char **argv)
   {	

     ros::init(argc, argv, "nodeC");
   
     /*se inicia la comunicación con el sistema ROS*/

     ros::NodeHandle c;

	/*se crea un objeto tipo subscriber, con la funcion .subscribe se retorna un objeto de este tipo y se especifica el nombre del topic, 		el tamaño del buffer que guarda los mensajes si estos se reciben mas rápido de lo que se pueden procesar y se llama la función creada 		al principio indicando que se recibió un mensaje nuevo*/
   
          ros::Subscriber subsC = c.subscribe("chatC", 1000, chatterCallback);
   


//SECCIÓN DE PUBLISHER DEL NODO

   
    /* con la función node.advertise() se obtiene un objeto tipo publisher que permitirá publicar topics. con advertise de <std_msgs::String> 		se especifica que se publicarpa un topic de variable String. el primer parámetro especifica el nombre del topic y el segundo el tamaño 		del buffer o "cola" que funciona como bandeja en caso que los mensajes son publicados más rapido de lo que se pueden enviar*/

     ros::Publisher pubC = c.advertise<std_msgs::String>("chatF", 1000);

   /*Rate permite especificar la frecuencia con que se desea publicar el topic (en este caso 10Hz)*/

     ros::Rate loop_rate(1);
   /*crea una variable que llevará la cuenta de cuantos mensajes se han enviado y se inicia el ciclo que mantendrá activo el nodo*/
     
     int count = 0;
     int valor = entero.data;
     double vb = 0;
     double vm = 0;
     double va = 0;

     while (ros::ok())
     {
       /*se crea una variable del mismo tipo que se especificó en el topic que se publicará, además se imprime para visualizar el mensaje en el 	terminal con ROS_INFO*/

       std_msgs::String msg;
       std::string s_0 = "";
       std::string s_1 = "";
       std::string s_2 = "";
        
 
       /*std::stringstream ss;
       ss << "hello world " << count;
       msg.data = ss.str();*/
     ROS_INFO("I heard: [%d]", valor);

       if(entero.data<=530)
       {
	 msg.data="Bajo=100%//Medio=0%//Alto=0%";
       }
   
       if(entero.data>530 & entero.data<715)
       {
	 vb=(-0.27027*entero.data)+243.2431;
         vm=(0.54054*entero.data)-286.4862;
         va=(0.27027*entero.data)-143.2431;
       s_0 = static_cast<std::ostringstream*>(&(std::ostringstream() << vb))->str();
       s_1 = static_cast<std::ostringstream*>(&(std::ostringstream() << vm))->str();
       s_2 = static_cast<std::ostringstream*>(&(std::ostringstream() << va))->str();  
         msg.data="Bajo="+ s_0 + "%""//Medio="+ s_1 + "%" "//Alto="+ s_2+ "%";
       }
      if(valor>=715 & valor<900)
       {
	 vb=(-0.27027*entero.data)+243.2431;
         vm=(-0.54054*entero.data)+486.4862;
         va=(0.27027*entero.data)-143.2431;
         s_0 = static_cast<std::ostringstream*>(&(std::ostringstream() << vb))->str();
       s_1 = static_cast<std::ostringstream*>(&(std::ostringstream() << vm))->str();
       s_2 = static_cast<std::ostringstream*>(&(std::ostringstream() << va))->str();  
         msg.data="Bajo="+ s_0 + "%""//Medio="+ s_1 + "%" "//Alto="+ s_2+ "%";
         msg.data="Bajo=%//Medio=%//Alto=%";
       }
      if(valor>=900)
       {
         
         msg.data="Bajo=0%//Medio=0%//Alto=100%";
       }
       ROS_INFO("%s", msg.data.c_str());
   
      /*La función publish() es la que se utiliza para publicar el mensaje y el parámetro es el objeto creado que almacena el contenido a 		enviar y debe ser el mismo especificado en la funcion advertise()*/

      pubC.publish(msg);
  
	/*la siguiente función permite que lleguen las callbacks de los nodos que se suscriban al topic que está publicando*/
      
	ros::spinOnce();

  	/*con rate.sleep() se complementa la frecuencia para evitar que se publiquen topics a una frecuencia diferente a la especificada anterionrmente*/

      loop_rate.sleep();
      ++count;
    }
    /*realiza el callback al nodo publisher*/
    ros::spin();
    return 0;
   }
