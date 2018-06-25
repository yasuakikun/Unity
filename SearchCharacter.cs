using UnityEngine;
using System.Collections;

public class SearchCharacter : MonoBehaviour
{

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
        if (col.tag == "Player")
        {
            Debug.Log("見失う");
            GetComponentInParent<MoveEnemy>().SetState("wait");
        }
    }

    void Start()
    {
    }

    void Update()
    { 
    }
}
