   #include "ros/ros.h"
   #include "std_msgs/String.h"
   #include "std_msgs/Char.h"
   #include <sstream>

   
   //SECCIÓN DE SUBSCRIBER DEL NODO

   //explicación nodo subscriber sencillo 

   /*la función se llamará cuando llegue un nuevo mensaje en el topic chatter*/

   std_msgs::String mensaje;

   void chatterCallback(const std_msgs::String::ConstPtr& msgE)
   {
     mensaje.data=msgE->data;

     ROS_INFO("I heard: [%s]", mensaje.data.c_str());
   }
   
   int main(int argc, char **argv)
   {	

     ros::init(argc, argv, "nodeE");
   
     /*se inicia la comunicación con el sistema ROS*/

     ros::NodeHandle e;

	/*se crea un objeto tipo subscriber, con la funcion .subscribe se retorna un objeto de este tipo y se especifica el nombre del topic, 		el tamaño del buffer que guarda los mensajes si estos se reciben mas rápido de lo que se pueden procesar y se llama la función creada 		al principio indicando que se recibió un mensaje nuevo*/
   
          ros::Subscriber subsE = e.subscribe("chatE", 1000, chatterCallback);
   
     /*realiza el callback al nodo publisher*/
     
        


//SECCIÓN DE PUBLISHER DEL NODO

   
    /* con la función node.advertise() se obtiene un objeto tipo publisher que permitirá publicar topics. con advertise de <std_msgs::String> 		se especifica que se publicarpa un topic de variable String. el primer parámetro especifica el nombre del topic y el segundo el tamaño 		del buffer o "cola" que funciona como bandeja en caso que los mensajes son publicados más rapido de lo que se pueden enviar*/

     ros::Publisher pubE = e.advertise<std_msgs::Char>("chatE2H", 1000);

   /*Rate permite especificar la frecuencia con que se desea publicar el topic (en este caso 10Hz)*/

     ros::Rate loop_rate(0.5);
   /*crea una variable que llevará la cuenta de cuantos mensajes se han enviado y se inicia el ciclo que mantendrá activo el nodo*/
     
     int count = 0;
     while (ros::ok())
     {
       /*se crea una variable del mismo tipo que se especificó en el topic que se publicará, además se imprime para visualizar el mensaje en el 	terminal con ROS_INFO*/

       std_msgs::Char car;
   
       /*std::stringstream ss;
       ss << "hello world " << count;
       msg.data = ss.str();*/
   
       //ROS_INFO("%s", msg.data.c_str());
       
       car.data='A';
       
   
      /*La función publish() es la que se utiliza para publicar el mensaje y el parámetro es el objeto creado que almacena el contenido a 		enviar y debe ser el mismo especificado en la funcion advertise()*/

      pubE.publish(car);
  
	/*la siguiente función permite que lleguen las callbacks de los nodos que se suscriban al topic que está publicando*/
      
	ros::spinOnce();

  	/*con rate.sleep() se complementa la frecuencia para evitar que se publiquen topics a una frecuencia diferente a la especificada anterionrmente*/

      loop_rate.sleep();
      ++count;
    }
    ros::spin();
    return 0;
   }
