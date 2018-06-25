using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HPBar : MonoBehaviour
{

    private GameObject player;
    private PlayerHP hpcomp;
    private Slider hpslider;
    private int hp;
    private int HPy;


    // Use this for initialization
    void Start ()
    {
        player = GameObject.Find("Player");
        hpcomp = GetComponent<PlayerHP>();
        hpslider = GameObject.Find("Shell").GetComponent<Slider>();
        hp = 100;　// 最大HPの値
        hpslider.value = hp;
    }

    //Update is called once per frame
	void Update ()
    {
        HPy = hpcomp.HP;
        hpslider.value = HPy;
    }
}
