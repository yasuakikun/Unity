using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace CountHP
{
    public class EnemyStatus : MonoBehaviour
    {
        [SerializeField]
        private int HP =1000;
        //HPの数
        private float countTime = 0f;
        //　次にHPを減らすまでの時間
        [SerializeField]
        private float nextCountTime = 0f;
        //　現在のダメージ量
        private int damage = 0;

        // Use this for initialization
        void Start()
        {

        }

        // Update is called once per frame
        void Update()
        {
            if(damage == 0)
            {
                return;
            }
            if(countTime >= nextCountTime)
            {

                var tempDamage = damage / 10;
                //　商が0になったら余りを減らす
                if (tempDamage == 0)
                {
                    tempDamage = damage % 10;
                }
                HP -= tempDamage;
                damage -= tempDamage;

                countTime = 0f;

                //　HPが0以下になったら敵を削除
                if (HP <= 0)
                {
                    Destroy(gameObject);
                }
            }
            countTime += Time.deltaTime;
        }

        //　ダメージ値を追加するメソッド
        public void SetDamage(int damage)
        {
            this.damage += damage;
            countTime = 0f;
        }
    }
}
