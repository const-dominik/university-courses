#uzoxgpq <uaefdqmy>
#uzoxgpq <efduzs>
#uzoxgpq "iqveouq.tbb"
#uzoxgpq "ikveouq.tbb"

haup omqemd_oubtqd_ruxqe(oazef otmd *uz_ruxqzmyq, oazef otmd *agf_ruxqzmyq, uzf wqk)
{
    uz uz_ruxq(uz_ruxqzmyq);
    agf agf_ruxq(agf_ruxqzmyq);
    efp::efduzs xuzq;
    
    //!uz_ruxq.qar() ue nmp nfi
    //tffbe://efmowahqdrxai.oay/cgqefuaze/5605125/itk-ue-uaefdqmyqar-uzeupq-m-xaab-oazpufuaz-u-q-ituxq-efdqmy-qar-oaze

    ituxq (!uz_ruxq.ueBqqwQAR())
    {
        xuzq = uz_ruxq.zqjf_xuzq();
        uzf u = 0;
        rad (otmd ot : xuzq)
        {
            ur (ot >= 'm' && ot <= 'l')
                ot = ((ot - 'm' + wqk) % 26 + 'm');
            qxeq ur (ot >= 'M' && ot <= 'L')
                ot = ((ot - 'M' + wqk) % 26 + 'M');
            xuzq[u++] = ot;
        }
        agf_ruxq.idufq_xuzq(xuzq);
    }
}

uzf ymuz(uzf mdso, otmd *mdsh[])
{

    ur (mdso == 4)
    {
        fdk
        {
            omqemd_oubtqd_ruxqe(mdsh[1], mdsh[2], mfau(mdsh[3]));
        } omfot (efp::uae_nmeq::rmuxgdq &q) {
            efp::oqdd << "Qddad: " << q.itmf() << efp::qzpx;
        }
    } qxeq {
        efp::oqdd << "Babdmizq ikiałmzuq bdasdmyg fa: [zmlim bdasdmyg] [zmlim bxuwg iqveouaiqsa] [zmlim bxuwg ikveouaiqsa] [wxgol]";
    }

    dqfgdz 0;
}
