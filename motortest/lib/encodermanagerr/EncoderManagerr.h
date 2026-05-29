#ifndef EncoderManagerr_h
#define EncoderManagerr_h

#include <Zumo32U4.h>

/**
 * @class EncoderManager
 * @brief Beheert encoder data van de Zumo robot.
 *
 * Deze klasse houdt de encoderwaarden bij en berekent
 * het verschil tussen opeenvolgende metingen.
 */
class EncoderManager
{
private:
    /**
     * @brief Totale waarde van linker encoder.
     */
    int leftCount;

    /**
     * @brief Totale waarde van rechter encoder.
     */
    int rightCount;

    /**
     * @brief Vorige waarde van linker encoder.
     */
    int previousLeft;

    /**
     * @brief Vorige waarde van rechter encoder.
     */
    int previousRight;

public:
    /**
     * @brief Constructor van EncoderManager.
     */
    EncoderManager();

    /**
     * @brief Update encoderwaarden.
     */
    void update();

    /**
     * @brief Print encoderdata naar Serial Monitor.
     */
    void printData();
    int getLeftCount();
    int getRightCount();
};

#endif