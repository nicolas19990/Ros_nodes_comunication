   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include <sstream>
   #include "std_msgs/Float32.h"
   
   //SECCIÓN DE SUBSCRIBER DEL NODO

   //explicación nodo subscriber sencillo 

   /*la función se llamará cuando llegue un nuevo mensaje en el topic chatter*/

   std_msgs::Float32 flotante;

   void chatterCallback(const std_msgs::Float32::ConstPtr& flot)
   {
     flotante.data=flot->data;
     
     ROS_INFO("I heard: [%f]", flotante.data);
   }
   
   int main(int argc, char **argv)
   {	

     ros::init(argc, argv, "nodeD");
   
     /*se inicia la comunicación con el sistema ROS*/

     ros::NodeHandle d;

	/*se crea un objeto tipo subscriber, con la funcion .subscribe se retorna un objeto de este tipo y se especifica el nombre del topic, 		el tamaño del buffer que guarda los mensajes si estos se reciben mas rápido de lo que se pueden procesar y se llama la función creada 		al principio indicando que se recibió un mensaje nuevo*/
   
          ros::Subscriber subsD = d.subscribe("chatD", 1000, chatterCallback);
   
     /*realiza el callback al nodo publisher*/
     
        


//SECCIÓN DE PUBLISHER DEL NODO

   
    /* con la función node.advertise() se obtiene un objeto tipo publisher que permitirá publicar topics. con advertise de <std_msgs::String> 		se especifica que se publicarpa un topic de variable String. el primer parámetro especifica el nombre del topic y el segundo el tamaño 		del buffer o "cola" que funciona como bandeja en caso que los mensajes son publicados más rapido de lo que se pueden enviar*/

     ros::Publisher pubD = d.advertise<std_msgs::String>("chatG", 1000);

   /*Rate permite especificar la frecuencia con que se desea publicar el topic (en este caso 10Hz)*/

     ros::Rate loop_rate(1);
   /*crea una variable que llevará la cuenta de cuantos mensajes se han enviado y se inicia el ciclo que mantendrá activo el nodo*/
     double vb = 0;
     double vm = 0;
     double va = 0;
       std::string s_0 = "";
       std::string s_1 = "";
       std::string s_2 = "";
       std_msgs::String msg; 
        
     int count = 0;
     while (ros::ok())
     {
       /*se crea una variable del mismo tipo que se especificó en el topic que se publicará, además se imprime para visualizar el mensaje en el 	terminal con ROS_INFO*/

   
       
       if(flotante.data<=28.5)
       {
	 msg.data="Bajo=100%//Medio=0%//Alto=0%";
       }
   
       if(flotante.data>28.5 & flotante.data<33.5)
       {
	 vb=(-10*flotante.data)+385;
         vm=(20*flotante.data)-570;
         va=(10*flotante.data)-285;
       s_0 = static_cast<std::ostringstream*>(&(std::ostringstream() << vb))->str();
       s_1 = static_cast<std::ostringstream*>(&(std::ostringstream() << vm))->str();
       s_2 = static_cast<std::ostringstream*>(&(std::ostringstream() << va))->str();  
         msg.data="Bajo="+ s_0 + "%""//Medio="+ s_1 + "%" "//Alto="+ s_2+ "%";
       }
      if(flotante.data>=33.5 & flotante.data<38.5)
       {
	 vb=(-10*flotante.data)+385;
         vm=(-20*flotante.data)+770;
         va=(10*flotante.data)-285;
         s_0 = static_cast<std::ostringstream*>(&(std::ostringstream() << vb))->str();
       s_1 = static_cast<std::ostringstream*>(&(std::ostringstream() << vm))->str();
       s_2 = static_cast<std::ostringstream*>(&(std::ostringstream() << va))->str();  
         msg.data="Bajo="+ s_0 + "%""//Medio="+ s_1 + "%" "//Alto="+ s_2+ "%";
         msg.data="Bajo=%//Medio=%//Alto=%";
       }
      if(flotante.data>=38.5)
       {
         
         msg.data="Bajo=0%//Medio=0%//Alto=100%";
       }
   
       ROS_INFO("%s", msg.data.c_str());
   
      /*La función publish() es la que se utiliza para publicar el mensaje y el parámetro es el objeto creado que almacena el contenido a 		enviar y debe ser el mismo especificado en la funcion advertise()*/

      pubD.publish(msg);
  
	/*la siguiente función permite que lleguen las callbacks de los nodos que se suscriban al topic que está publicando*/
      
	ros::spinOnce();

  	/*con rate.sleep() se complementa la frecuencia para evitar que se publiquen topics a una frecuencia diferente a la especificada anterionrmente*/

      loop_rate.sleep();
      ++count;
    }
    ros::spin();
    return 0;
   }

