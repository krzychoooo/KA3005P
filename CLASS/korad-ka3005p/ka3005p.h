/*
 * zachowajta mój email i róbta co chceta.
 */

/*
 * File:   ka3005p.h
 * Author: fajnysoft@gmail.com
 *
 * Created on 20 kwietnia 2017, 17:51
 */

#ifndef KA3005P_H
#define KA3005P_H


class ka3005p {

public:
    int comport_number;
    int baudrate;
    const char *mode; //serial port mode
    static const char modeCoradKA3005P[4];
    enum KA3005P_STAT {
        CC=0,
        CV=1,
        INDEPENDENT=0,
        SERIES=1,
        PARALLEL=3,
        OFF=0,
        ON=1,
        LOCK=0,
        UNLOCK=1
    };
    /** \struct stat
    * \brief struktura zawierająca stan zasilacza
    */

    struct stat{
        int ch1Mode;    //0=CC mode, 1=CV mode
        int ch2Mode;  //0=CC mode, 1=CV mode
        int tracking;   //00=Independent, 01=Tracking series,11=Tracking parallel
        int beep;       //0=Off, 1=On
        int lock;       //0=Lock, 1=Unlock
        int output;     //0=Off, 1=On
    } ;
    stat status;
    ka3005p();
    /**\<html><h3>tworzy uchwyt do zasilacza na porcie 'com'</h3><p></p></html>
     * \param com int
     * \return void
     */
    ka3005p(int);
    ka3005p(int, int, const char *);
    virtual ~ka3005p();

    /**\<html><h3>ustawia napięcie 'volt' w kanale 'ch'</h3><p></p></html>
     * \param ch int
     * \param volt float
     * \return void
     */
    void setV(int, float);

    /**\<html><h3>ustawia prąd 'current' w kanale 'ch'</h3><p></p></html>
     * \param ch int
     * \param current float
     * \return void
     */
    void setI(int, float);

    /**\<html><h3>włącza wyłącza wyjście</h3><p></p></html>
     * \param enable bool
     * \return void
     */
    void powerEnable(bool);

    /**\<html><h3>oblicza i zwraca moc wyjściową w kanale 'ch'</h3><p></p></html>
     * \param ch int
     * \return float
     */
    float getPower(int);

    /**\<html><h3>zwraca napięcie wyjściowe w kanale 'ch'</h3><p></p></html>
     * \param ch int
     * \return float
     */
    float getVoltage(int);

    /**\<html><h3>zwraca prąd wyjściowe w kanale 'ch'</h3><p></p></html>
     * \param ch int
     * \return float
     */
    float getCurrent(int);

    /**\<html><h3>zwraca wskaźnik do struktury </h3><p></p></html>
     * \return stat pointer
     */
    stat * getStatus();

        /**\<html><h3>zwraca numer portu com </h3><p></p></html>
     * \return com int
     */
    void getCom();
private:

};

#endif /* KA3005P_H */

