#ifndef __PROGRESSBAR_H__
#define __PROGRESSBAR_H__

#include <qprogressbar.h>
#include "kernel/pdfwriter.h"

namespace gui {

/** Progress observer adapter.
 * Implementation of IProgressBar which delegates all operations to wrapped
 * Qt progress bar. This has to be created and destroyed by user (this is
 * because Qt memmory management).
 * <br>
 * Instance can be used in ProgressObserver IObserver implementation.
 * <br>
 * <pre>
 * Example:
 *
 * // Creates QProgressBar instance
 * QProgressBar * qtProgressBar=new QProgressBar();
 *
 * // Creates adapter
 * ProgressBar * progressBar=new ProgressBar(qtProgressBar);
 * 
 * // Creates and registers observer to process which progress we 
 * // want to display
 * shared_ptr<ProgressObserver> progressObserver(new ProgressObserver(progressBar));
 * process->registerObserver(progressObserver);
 *
 * </pre>
 * 
 * In single thread application we can reuse progressObserver on more processes
 * and have one progress bar vizualizator for all of them. In multithread 
 * applications where such processes runs in different threads this may be 
 * problem because this class doesn't use any kind of synchronization.
 */
class ProgressBar: public pdfobjects::utils::IProgressBar
{
        /** Displayer of progress.
         * This instance is allocated and deallocated by instance user.
         */
        QProgressBar * progressBar;
public:
        /** Initialization constructor.
         * @param pB Qt progress bar instance.
         */
        ProgressBar(QProgressBar * pB):progressBar(pB)
        {
        }
        
        /** Returns qt progress bar visualizator.
         * @return progressBar pointer.
         */
        QProgressBar * getProgressBar()
        {
                return progressBar;
        }

        /** Progress initiator.
         * Shows qt progress bar and sets its state to 0.
         */
        void start();

        /** Progress terminator.
         * Hides qt progress bar.
         */
        void finish();

        /** Sets maximum step count.
         * @param maxStep Number of steps of the process.
         */
        void setMaxStep(int maxStep);


        /** Updates progress state.
         * @param step Number of current steps from process start.
         */
        void update(int step);
};

} // gui namespace

#endif
