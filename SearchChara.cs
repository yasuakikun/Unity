using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SearchChara : MonoBehaviour{

    public enum State
    {
        Walk = 3,
        Wait = 7,
        Chase = 5,
        Attack = 1,
        Freeze = 9
    };

    void OnTriggerStay(Collider col)
    {
        //　プレイヤーキャラクターを発見
        if (col.tag == "Player")
        {

            //　敵キャラクターの状態を取得
            MoveEnemy.EnemyState state = GetComponentInParent<MoveEnemy>().GetState();
            //　敵キャラクターが追いかける状態でなければ追いかける設定に変更
            if (state != MoveEnemy.EnemyState.Chase)
            {
                Debug.Log("プレイヤー発見");
                GetComponentInParent<MoveEnemy>().SetState("chase", col.transform);
            }
        }
    }
 
    void OnTriggerExit(Collider col)
    {
        //　プレイヤーキャラクターを発	
        if (col.tag == "Player")
        {
            Debug.Log("見失う");
            GetComponentInParent<MoveEnemy>().SetState("wait");
        }
    }

    void Start()
    {
    }
  
 
	// Update is called once per frame
	void Update ()
    {
		
	}
}
