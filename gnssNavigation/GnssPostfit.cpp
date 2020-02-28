/**
 *  @file   GNSSPostfit.cpp
 *  @author Ryan
 *  @brief  Implementation file for GNSS postfit analysis
 **/

#include "GnssPostfit.h"
#include "miniblas/miniblas.h"


vector<double> getResiduals( minivector& nomXYZ, std::map<int,minivector> &results,const vector<rnxData>& data)
{
    /*
     * inputs ::
     *   nomXYZ --> nominal ECEF platform position. [Point3]
     *   results --> optimized solution [Values]
     *   data --> observed GNSS data [vector<rnxData>]
     * output ::
     *   postFit --> GNSS postfit residuals [vector<double>]
     */
    unsigned int epoch = 0;
    unsigned int epochKey = 0;
    vector<double> postFit;

    foreach (const auto& keypair, results)
    {

        minivector q = keypair.second;
        while ( epochKey == get<1>(data[epoch]) )
        {
            minivector h = obsMap(get<3>(data[epoch]),nomXYZ, 1);
            //double est = h.transpose() * q;
            double est;
            miniblas_ddot(h,q,&est);
            double residual = est - (get<5>(data[epoch]) - get<4>(data[epoch]));
            postFit.push_back(residual);
            epoch++;
        }
        epochKey++;
    }
    return postFit;
}

void writeResiduals(const vector<double>& postfitResiduals, string outputFile,const vector<string>& index )
{
    /*
     * inputs ::
     *  postfitResiduals --> GNSS postfit residuals [vector<double>]
     *  outputFile --> specify the destination file name [string]
     *  index --> unique idetifier for GNSS residuals (i.e. SVN) [ vector<string>]
     * outputs ::
     *  std out
     */
    ofstream outFile(outputFile.c_str());
    for( unsigned int i = 0; i < postfitResiduals.size(); i++)
    {
        outFile << index[i] << " " << " " <<  postfitResiduals[i] << endl;
    }
}

vector<int> markResiduals(const vector<double>& postfitResdiuals, double threshold )
{
    /*
     * inputs ::
     *  postfitResiduals --> GNSS postfit residuals [vector<double>]
     *  threshold --> theshold for labeling residual as outlier.
     * outputs ::
     *  markedOutliers --> label vector to specify if observable is an outlier [vector<int>]
     */
    vector<size_t> residuals(postfitResdiuals.size());
    vector<int> markedOutliers;
    iota(residuals.begin(), residuals.end(), 0);
    copy_if(residuals.begin(), residuals.end(), back_inserter(markedOutliers), [=](size_t i)
    {
        return std::abs(postfitResdiuals[i]) > threshold;
    });
    return markedOutliers;
}
