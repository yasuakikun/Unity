using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public  class PlayerHP : MonoBehaviour
{

    private MoveEnemy moveEnemy;
    private YureCamera yurecamera;
    private MyChara myChara;
    private Canvas canvas;

    
    //マックスHP2
    public int maxHP = 1000;
    //受けるダメージ
    public int ZombieDamage = 20;
    public int WolfDamage = 30;
    public int HobgoDamage = 40;
    public int goblinDamage = 30;
    public int trollDamage = 60;
    //現在のプレイヤーのHP

    public int HP;

    void Start()
    {
        moveEnemy = GetComponent<MoveEnemy>();
        yurecamera = GetComponent<YureCamera>();
        myChara = GetComponent<MyChara>();
        canvas = GetComponent<Canvas>();

        //HPのマックスHP
        HP = maxHP;
    }

    void Update()
    {
        if(HP < 0)
        {
            Debug.Log("ゲームオーバー");
            //Destroy(gameObject);
        }
    }

    public void OnTriggerEnter(Collider hit)
    {
        switch (hit.gameObject.tag)
        {
            case "EnemyHit":
                //yurecamera.Shake(GameObject.Find("MainCamera"));
                HP -= ZombieDamage;
                break;
            case "WolfHit":
                HP -= WolfDamage;
                break;
            case "HobgoHit":
                HP -= HobgoDamage;
                break;
            case "goblinHit":
                HP -= HobgoDamage;
                break;
            case "TrollHit":
                HP -= trollDamage;
                break;
        }
    }
}