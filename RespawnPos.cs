using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RespawnPos : MonoBehaviour {

    [SerializeField]
     GameObject[] enemy;
    //次の沸く時間
    [SerializeField]  float Respawntime;
    //リスする数 
    [SerializeField]  int ResNumber;
    //何人リスポンしたか数
    private int ResCheckNumber;
    //経過時間
    private float movetime;
    // Use this for initialization

    void RespawnEnemy()
    {
        //敵ランダム生成
        var RandomRes = Random.Range(0,enemy.Length);
        //ランダムな向きに生成する //角度を掛ける
        var Randomdirection = Random.value * 360;

       GameObject.Instantiate(enemy[RandomRes], transform.position, Quaternion.Euler(0f,Randomdirection,0f));

        ResCheckNumber++;
        movetime = 0f;
    }

    void Start ()
    {
        //初期化リスする数と経過時間
        ResCheckNumber = 0;
        movetime = 0f;
	}
	
	// Update is called once per frame
	void Update ()
    {
        //リスポンした数がリスした数より超えていたら、リターンする
		if(ResCheckNumber >= ResNumber)
        {
            return;
        }
        movetime += Time.deltaTime;

        //経過時間がリスする数より超えていたら敵をリスさせる
        //経過時間を０にもどす、
        if(movetime > Respawntime)
        {
            movetime = 0.0f;
            RespawnEnemy();
        }
	}
}
