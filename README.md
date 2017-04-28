# KA3005P


https://youtu.be/yGm5sAkr9yg


Funkcje klasy ka3005p:

1. ka3005p(int) - konstruktor, podajemy nr portu com

2. void setV(int, float) - ustawia napięcie 'volt' w kanale 'ch'
     * \param ch int              nr kanału zasilacza.
     * \param volt float        napięcie
     * \return void
     */

3. void setI(int, float); - ustawia prąd 'current' w kanale 'ch'
     * \param ch int
     * \param current float
     * \return void
     */
   
4.  void powerEnable(bool); - włącza wyłącza wyjście
     * \param enable bool
     * \return void
     */

5.   float getPower(int);  - oblicza i zwraca moc wyjściową w kanale 'ch'
     * \param ch int
     * \return float
     */

6.    float getVoltage(int); - zwraca napięcie wyjściowe w kanale 'ch'
     * \param ch int
     * \return float
     */

7.  float getCurrent(int); - zwraca prąd wyjściowe w kanale 'ch'
     * \param ch int
     * \return float
     */

8. stat * getStatus(); - zwraca wskaźnik do struktury 
     * \return stat pointer
     */
     Struktura:
                     struct stat{
                     int ch1Mode;    //0=CC mode, 1=CV mode
                     int ch2Mode;  //0=CC mode, 1=CV mode
                     int tracking;   //00=Independent, 01=Tracking series,11=Tracking parallel
                    int beep;       //0=Off, 1=On
                    int lock;       //0=Lock, 1=Unlock
                    int output;     //0=Off, 1=On
                    } ;    

9.     void getCom(); - zwraca numer portu com
     * \return com int
     */
 

Funkcje klasy csv:

1. csv(string); konstruktor, podajemy plik o nazwie fName
     * \param fName
     * \return void
     */

2.     void addToRecord(float); - funkcja dopisująca do rekordu kolejne pomiary. Tworzy linię w pliku csv kolejne wartości rozdzielone znakiem';' Znak dziesiętny to ','
     * \param fPomiar float
     * \return void
     */

3. void storeRecord(); - zapisuje do pliku kolejny rekord
     * \return void
     */


