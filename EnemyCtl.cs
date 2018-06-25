using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyCtl : MonoBehaviour {

    private CountHP.EnemyStatus status;
	// Use this for initialization
	void Start ()
    {
        status = GetComponent<CountHP.EnemyStatus>();
	}
	
    public void Damage(int damage)
    {
        status.SetDamage(damage);
    }

	// Update is called once per frame
	void Update ()
    {
		
	}
}
