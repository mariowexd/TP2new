#include "jugador.h"

Jugador::Jugador(char ide, string texnom, int fichasIniciales){
  for(int x=0; x<6; x++){
    cartas[x]=0;
  }
  pierdeTurno=false;
  gano=false;
  id=ide;
  fichasPorColocar=fichasIniciales;
  textoNombre=texnom;
}
Jugador::~Jugador(){
}
int Jugador::getCantCartasDeUnTipo(int a){
  return cartas[a];
}
bool Jugador::getPierdeTurno(){
  return pierdeTurno;
}
bool Jugador::getGano(){
  return gano;
}
char Jugador::getId(){
  return id;
}
int Jugador::getFichasPorColocar(){
  return fichasPorColocar;
}
string Jugador::getTextoNombre(){
  return textoNombre;
}

void Jugador::setPierdeTurno(bool a){
  pierdeTurno = a;
}
void Jugador::setGano(bool a){
  gano = a;
}
void Jugador::setId(char nom){
  id = nom;
}
void Jugador::setFichasPorColocar(int cant){
  fichasPorColocar = cant;
}
void Jugador::setTextoNombre(string a){
  textoNombre=a;
}
/*
    PRE: recibe como parametro un puntero a tablero
    POST: declara tres variables locales, ancho, profundidad y alto las cuales son verificadas y en el caso de ser coordenadas validas de una casilla que no esta bloqueada ni ocupada se le ingresa una ficha.
*/
void Jugador::colocarFicha(Tablero* tablero) {
    tablero->imprimirTablero();
    int ancho, profundidad, alto;

    cout << "Seleccione una posicion (ancho, profundidad y altura respectivamente) para ingresar una ficha en esa posicion" << endl;

    this->ingresarVerificandoValores(ancho, profundidad, alto, tablero);

    while (tablero->getCasillero(profundidad, ancho, alto)->getBloqueado() == true || tablero->getCasillero(profundidad, ancho, alto)->getId() != 0) {

        if (tablero->getCasillero(profundidad, ancho, alto)->getBloqueado() != false) {
            cout << "la posicion ingresada esta bloqueada!!!" << endl;
        }

        else {
            cout << "la posicion elegida ya esta ocupada!!!" << endl;
        }
        cout << "Elija otra posicion en la cual ingresar la ficha!!!" << endl << endl;
        colocarFicha(tablero);
    }
    tablero->getCasillero(profundidad, ancho, alto)->setId(this->getId());

    this->setFichasPorColocar(this->getFichasPorColocar() - 1);

}

/*
    PRE: recibe por parametros la direccion de memoria de cada atributo del casillero (ancho, profundidad y alto) y el puntero al tablero.
    POST: le pregunta al usuario sobre los valores de ancho, profundidad y altura y luego se los otorga a las variables que fueron pasadas por referencia, siempre verificando que los valores que
    otorgo el usuario sean validos.
*/
void  Jugador::ingresarVerificandoValores(int &ancho,int &profundidad,int &alto, Tablero* tablero) {

      cout << "Ancho: ";
      cin >> ancho;

      while (ancho<1 || ancho>tablero->getAncho()) {
          cout << "El ancho ingresado no es valido ingrese otro (el valor debe estar entre 0 y " << tablero->getAncho() << " ): ";
          cin >> ancho;
      }

      cout << "Profundidad: ";
      cin >> profundidad;

      while (profundidad<1 || profundidad>tablero->getProf()) {
          cout << "La profundidad ingresada no es valida ingrese otra (el valor debe estar entre 0 y " << tablero->getAncho() << " ): ";
          cin >> profundidad;
      }

        cout << "Alto: ";
        cin >> alto;

      while (alto<1 || alto>tablero->getAlto()){
          cout << "El alto ingresado no es valido ingrese otro (el valor debe estar entre 0 y " << tablero->getAncho() << " ): ";
          cin >> alto;
      }
 }

/*
    PRE: recibe como parametro un puntero a tablero.
    POST: mueve una ficha de un casillero a un casillero que se encuentre al lado del mismo (no puede moverse en diagonal).
*/

void Jugador::moverFicha(Tablero* tablero) {
    tablero->imprimirTablero();
    int ancho, profundidad, alto;
    int anchoDestino, profundidadDestino, altoDestino;
    Casillero *casillero, *casilleroDestino;

    cout << "Seleccione una posicion (ancho, profundidad y altura respectivamente) para mover una ficha de esa posicion" << endl;
    this->ingresarVerificandoValores(ancho, profundidad, alto, tablero);

    casillero= this->encontrarCasillero(tablero, profundidad, ancho, alto);

    cout << "Seleccione una posicion en la cual mover la ficha elegida(no se puede mover en diagonal): "<<endl;
    this->ingresarVerificandoValores(anchoDestino, profundidadDestino, altoDestino, tablero);

    while (anchoDestino != ancho + 1 || anchoDestino != ancho - 1 || profundidadDestino != profundidad - 1 || profundidadDestino != profundidad + 1 || altoDestino != alto + 1 || altoDestino != alto - 1 || tablero->getCasillero(profundidadDestino, anchoDestino, altoDestino)->getBloqueado() == true || tablero->getCasillero(profundidadDestino, anchoDestino, altoDestino)->getId() == 0) {
        if (tablero->getCasillero(profundidadDestino, anchoDestino, altoDestino)->getBloqueado()==true || tablero->getCasillero(profundidadDestino, anchoDestino, altoDestino)->getId()==0)
        {
            cout << "La casilla a la cual se quiere mover la ficha esta ocupada o bloqueada intente nuevamente!!!"<<endl;
        }
        else {
            cout << "La casilla ingresada no es valida intente nuevamente!!!" << endl;
        }
        cout << "Seleccione una nueva posicion valida en la cual mover la ficha elegida(no se puede mover en diagonal): " << endl<<endl;
        this->ingresarVerificandoValores(anchoDestino, profundidadDestino, altoDestino, tablero);
    }
    casilleroDestino = this->encontrarCasillero(tablero, profundidadDestino, anchoDestino, altoDestino);
    intercambiarFichas(casillero, casilleroDestino);
}

/*
    PRE: Recibe como parametros dos punteros a casilleros.
    POST: establece el id del casillero del cual se mueve la ficha a 0 y el id del casillero al cual se mueve la ficha se establece como el id del jugador que realizo el cambio.
*/

void Jugador::intercambiarFichas(Casillero* casillero, Casillero* casilleroAMover) {
    casilleroAMover->setId(this->getId());
    casillero->setId(0);
}

/*
    PRE: recibe como parametros el tablero y la profundidad, alto y ancho en el que se encuentra el casillero que se desea buscar.
    POST:devuelve el casillero en la profundidad, ancho y alto establecidos previamente.
*/

Casillero* Jugador::encontrarCasillero(Tablero* tablero, int profundidad, int ancho, int alto) {

    if (tablero->getCasillero(profundidad, ancho, alto)->getBloqueado() != false || tablero->getCasillero(profundidad, ancho, alto)->getId() != this->getId()) {

        if (tablero->getCasillero(profundidad, ancho, alto)->getBloqueado() != false) {
            cout << "la posicion ingresada esta bloqueada!!!" << endl;
        }

        else if (tablero->getCasillero(profundidad, ancho, alto)->getId() != 0) {
            cout << "Esta vacia o ocupada por otro jugador!!!" << endl;
        }

        cout << "Elija otra posicion en la cual ingresar la ficha" << endl << endl;
    }
    return tablero->getCasillero(profundidad, ancho, alto);
}

int Jugador::getCantTotalCartas(){

    int totalCartas = 0;

    for(int i=0; i<6; i++){
        totalCartas = totalCartas + this->getCantCartasDeUnTipo(i);
    }
    return totalCartas;
}

int Jugador::levantarCarta(int cantMaxCartas){

    if(this->getCantTotalCartas()>=cantMaxCartas){
        return -1;
    }
    int indiceCarta = this->generarIndiceCartaAleatorio();
    this->cartas[indiceCarta]++;
    return indiceCarta;
}

/// PRE: EL JUGADOR DEBE TENER AL MENOS UNA CARTA EN SU MANO. DE SER POSIBLE, SE JUGO LA CARTA Y SE LE QUITA DE LA MANO DEL JUGADOR
void Jugador::usarCarta(Lista<Jugador*>* jugadores, Tablero* tablero, int maximoDeCartas){
	if(jugadores->getCursor()==NULL) return;
    ///SI EL JUGADOR  NO TIENE CARTAS QUE JUGAR, SE LE LANZA UNA EXCEPCION
    if(this->getCantTotalCartas()<=0){
        throw "EL JUGADOR NO TIENE CARTAS QUE JUGAR. EL JUGADOR DEBE TENER AL MENOS UNA CARTA QUE USAR.";
    }
    int indiceCartaUsada = this->escojerCartaAUtilizar();///DEVUELVE EL INDICE DE LA CARTA A USAR

    if(indiceCartaUsada == 0){
        this->hacerPerderTurnoAJugador(jugadores);
    }
    if(indiceCartaUsada == 1){
        this->bloquearFichaDeJugador(jugadores);
    }
    if(indiceCartaUsada == 2){
        this->anularCasilleroDelTablero(tablero);
    }
    if(indiceCartaUsada == 3){
        this->revertirJugadaDeJugador(jugadores);
    }
    if(indiceCartaUsada == 4){
        this->destruirCartasDeJugador(jugadores);
    }
    if(indiceCartaUsada == 5){
        this->renovarCartas(maximoDeCartas);
    }
    this->cartas[indiceCartaUsada]--;
}

/****METODOS**PRIVADOS**PARA**USAR**CARTA***********************************************************************/

  /// MUESTRA AL JUGADOR LAS CARTAS QUE TIENE DISPONIBLES Y SE LE PIDE QUE INGRESE CUAL QUIERE USAR
  /// PRE: EL JUGADOR DEBE TENER AL MENOS UNA CARTA EN SU MANO
  /// POST: SE DEVUELVE EL INDICE DEL TIPO DE CARTA SELECCIONADA POR EL JUGADOR
int Jugador::escojerCartaAUtilizar(){

    bool seleccionValida = false;
    int entrada;

    do{
        cout<<"Seleccione el tipo de carta que desee utilizar:"<<endl<<endl
        <<"1. Hacer perder un turno a un jugador ("<<this->getCantCartasDeUnTipo(0)<<" cartas disponibles)."<<endl
        <<"2. Bloquear ficha de un jugador ("<<this->getCantCartasDeUnTipo(1)<<" cartas disponibles)."<<endl
        <<"3. Anular posicion del tablero ("<<this->getCantCartasDeUnTipo(2)<<" cartas disponibles)."<<endl
        <<"4. Volver atras una jugada del turno ("<<this->getCantCartasDeUnTipo(3)<<" cartas disponibles)."<<endl
        <<"5. Quitar cartas a un jugador ("<<this->getCantCartasDeUnTipo(0)<<" cartas disponibles)."<<endl
        <<"6. Renovar cartas en mano ("<<this->getCantCartasDeUnTipo(0)<<" cartas disponibles)."<<endl
        <<"Ingresar opcion: ";

        cin>>entrada;

        if(entrada >=1 && entrada<=6 && this->cartas[entrada-1]>0){
            seleccionValida = true;
        }
        if(!seleccionValida){
            cout<<"La opcion ingresada no es valida"<<endl<<endl;
        }
    }while(!seleccionValida);

    return entrada-1;
}

void Jugador::hacerPerderTurnoAJugador(Lista<Jugador*>* jugadores){

    Jugador* jugadorAfectado = this->pedirJugadorAPerjudicar(jugadores);///AUXILIAR QUE DEVUELVE PUNTERO DE JUGADOR
    if(jugadorAfectado){
        jugadorAfectado->setPierdeTurno(true);
    }
}

void Jugador::bloquearFichaDeJugador(Lista<Jugador*>* jugadores){

    Jugador* jugadorAfectado = this->pedirJugadorAPerjudicar(jugadores);

    /// VERIFICO QUE EL JUGADOR TENGA UNA FICHA EN TABLERO,
    /// SI LA TIENE SERA LA QUE CORRESPONDA AL CASILLERO DE SU JUGADA POSTERIOR
    if(jugadorAfectado && jugadorAfectado->getCasillaPosteriorJugada()){
        jugadorAfectado->getCasillaPosteriorJugada()->setBloqueado(true);
    }
}

///PRE: LA POSICION A ANULAR EN EL TABLERO DEBE SER UNA POSICION EXISTENTE VALIDA.
///PRE: EL CASILLERO EN DICHA POSICION DEBE DE ESTAR VACIO
///POST: EL CASILLERO EN DICHA POSICION QUEDA INHABILITADO Y NO PODRÁ SER OCUPADO HASTA EL SIGUIENTE TURNO
///      DEL JUGADOR QUE ANULO DICHO CASILLERO.
void Jugador::anularCasilleroDelTablero(Tablero* tablero){
    int prof, ancho, alto;
    bool casillaValida = false;

    do{
        cout<< "Seleccione una posicion libre del tablero (ancho, profundidad y altura) que desee anular" << endl;

        this->ingresarVerificandoValores(ancho, prof, alto, tablero);

        if(!tablero->getCasillero(prof, ancho, alto)->getOcupado()){
            casillaValida = true;

        }if(!casillaValida){
            cout<<"No se puede anular una posición ya ocupada. Ingrese una posición libre a anular."<<endl<<endl;
        }

    }while(!casillaValida);

    ///BLOQUEO LA CASILLA PARA QUE NO PUEDAN COLOCAR FICHAS EN ELLA Y SE LA ASIGNO AL JUGADOR
    /// PARA PODER DESBLOQUEARLA CUANDO SEA NUEVAMENTE SU TURNO.
    tablero->getCasillero(prof, ancho, alto)->setBloqueado(true);
    this->setCasillaAnulada(tablero->getCasillero(ancho, alto, prof));
}

///SI LA CASILLA PREVIA DEL JUGADOR AFECTADO ESTABA OCUPADA, ESTA CARTA NO TIENE EFECTO
void Jugador::revertirJugadaDeJugador(Lista<Jugador*>* jugadores){

    Jugador* jugadorAfectado =this->pedirJugadorAPerjudicar(jugadores);///AUXILIAR QUE DEVUELVE PUNTERO DE JUGADOR

    /// VERIFICO QUE EL JUGADOR TENGA UNA JUGADA PREVIA, SI LA TIENE, TMB TIENE UNA POSTERIOR(SU ULTIMO MOVIMIENTO)
    if(jugadorAfectado && jugadorAfectado->getCasillaPreviaJugada()){
        Casillero* jugadaPrevia = jugadorAfectado->getCasillaPreviaJugada();
        Casillero* jugadaPosterior = jugadorAfectado->getCasillaPosteriorJugada();
        ///SI ESA CASILLA QUE CORRESPONDE A LA JUGADA PREVIA ESTA VACIA,
        ///ENTONCES PODEMOS INTERCAMBIARLA POR LA JUGADA POSTERIOR
        if(!jugadorAfectado->getCasillaPreviaJugada()->getOcupado()){
            this->intercambiarFichas(jugadaPosterior, jugadaPrevia);
        }///SI LA CASILLA DE JUGADA PREVIA ESTABA OCUPADA POR OTRO JUGADOR, LA CARTA NO TUVO EFECTO
    }
}

void Jugador::destruirCartasDeJugador(Lista<Jugador*>* jugadores){

    Jugador* jugadorAfectado = this->pedirJugadorAPerjudicar(jugadores);

    if(jugadorAfectado){
        for(int i=0; i<6; i++){
            jugadorAfectado->cartas[i] = 0;
        }
    }
}

void Jugador::renovarCartas(int maximoDeCartas){

    int cantidadDeCartas = this->getCantTotalCartas() -1;///DESCUENTO LA QUE ESTA USANDO PARA QUE NO LEVANTE UNA DE MAS

    for(int i=0; i<6; i++){
        this->cartas[i] = 0;
    }

    for(int i=0; i<cantidadDeCartas; i++){
        this->levantarCarta(maximoDeCartas);
    }
}

Jugador* Jugador::pedirJugadorAPerjudicar(Lista<Jugador*>* jugadores){

    int id;
    /// EL ID DEL JUGADOR SE CORRESPONDE CON EL ORDEN EN LISTA DEL JUGADOR -> id == posicionDelJugadorEnLaLista
    /// DE EXISTIR EL JUGADOR, EL ID TIENE QUE SER MAYOR A CERO Y MENOR O IGUAL A LA CANTIDAD DE ELEMENTOS DE LA LISTA

    bool idExistente = false;

    do{
        cout<<"Favor de ingresar un ID válido del jugador al cual aplicar los efectos de la carta."<<endl<<endl;
        cin>>id;
        if(id <= (int)jugadores->contarElementos() && id > 0){
            idExistente = true;
        }
        if(!idExistente){
            cout<<"El ID ingresado no se corresponde a un ID existente válido"<<endl<<endl;
        }

    }while(!idExistente);

    ///YA SE QUE EXISTE Y SU POSICION EN LA LISTA SE CORRESPONDE AL ID
    ///DEVUELVO EL PUNTERO QUE OCUPA ESA POSICION EN LA LISTA
    return jugadores->get(id);

}

///DEVUELVE UN NUMERO AL AZAR ENTRE 0 Y 5
int Jugador::generarIndiceCartaAleatorio(){

    int aleatorio;
    srand(time(NULL));//ESTA LINEA ES POSIBLE QUE SI DA PROBLEMAS DEBA IR EN UNA LINEA FUERA DE LA CLASE(EN EL MAIN)
    aleatorio = rand();
    return aleatorio%6;
}

/****************************************************************************************************************/

/// GETTERS Y SETTERS QUE FALTAN

void Jugador::setCasillaPreviaJugada(Casillero* casillero){
    this->casillaPreviaJugada = casillero;
}
Casillero* Jugador::getCasillaPreviaJugada(){
    return this->casillaPreviaJugada;
}
void Jugador::setCasillaPosteriorJugada(Casillero* casillero){
    this->casillaPosteriorJugada = casillero;
}
Casillero* Jugador::getCasillaPosteriorJugada(){
    return this->casillaPosteriorJugada;
}
void Jugador::setCasillaAnulada(Casillero* casillero){
    this->casillaAnulada = casillero;
}
Casillero* Jugador::getCasillaAnulada(){
    return this->casillaAnulada;
}