using UnityEngine;
using System.Collections;
public enum WeaponType
{
    HG,
    SG,
    AR,
    SR
};
public class FPSWeaponStatus : MonoBehaviour
{

    //　銃の攻撃力
    [SerializeField]
    private float power = 1f;
    //　銃の射程距離
    [SerializeField]
    private float range = 999f;
    //　弾の最大装填数
    [SerializeField]
    private int maxCharge = 30;
    //　銃の種類
    [SerializeField]
    private WeaponType weaponType = WeaponType.AR;

    public float GetPower()
    {
        return power;
    }

    public float GetRange()
    {
        return range;
    }

    public int GetMaxCharge()
    {
        return maxCharge;
    }

    public WeaponType GetWeaponType()
    {
        return weaponType;
    }

}
